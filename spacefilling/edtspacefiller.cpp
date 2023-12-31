#include "edtspacefiller.h"
#include "atomspacefiller.h"
#include "gridspacefiller.h"
#include "../exceptions/optionexception.h"
#include <thread>
#include "../utils/Logger.h"

#include <iostream>
#include <queue>

using namespace am::pipeline;

double EDTSpaceFiller::euclideanDistance(const glm::vec3& p1, const glm::vec3& p2) {
	double dx = p2.x - p1.x;
	double dy = p2.y - p1.y;
	double dz = p2.z - p1.z;
	return std::sqrt (dx * dx + dy * dy + dz * dz);
}



void EDTSpaceFiller::func(std::promise<struct EDTSpaceFiller::Partial>&& p, am::math::Mat3D<GridPoint> volume, int zi, int zf, int index) {
	float MAX = INFINITY;
	am::math::Mat3D<float> tEDT(volume.width(), volume.height(), volume.depth(), -1);

	for (int z = zi; z < zf; z++) {
		am::math::Mat3D<float> R(volume.width(), volume.height(), 1);
		am::math::Mat3D<float> B(volume.width(), volume.height(), 1);
		am::math::Mat3D<float> L(volume.width(), volume.height(), 1);
		am::math::Mat3D<float> F(volume.width(), volume.height(), 1);
		am::math::Mat3D<float> LR(volume.width(), volume.height(), 1);
		am::math::Mat3D<float> BF(volume.width(), volume.height(), 1);


		for (int y = 0; y < volume.height(); y++) {
			L.at(0, y, 0) = volume.at(0, y, z).value == 0 ? 0 : -MAX;
			for (int x = 1; x < volume.width(); x++) {
				L.at(x, y, 0) = volume.at(x, y, z).value == 0 ? x : L.at(x - 1, y, 0);
			}
			R.at(volume.width() - 1, y, 0) = volume.at(volume.width() - 1, y, z).value == 0 ? volume.width() - 1 : MAX;
			for (int x = volume.width() - 2; x >= 0; x--) {
				R.at(x, y, 0) = volume.at(x, y, z).value == 0 ? x : R.at(x + 1, y, 0);
			}
		}
		for (int x = 0; x < volume.width(); x++) {
			B.at(x, 0, 0) = volume.at(x, 0, z).value == 0 ? 0 : -MAX;
			for (int y = 1; y < volume.height(); y++) {
				B.at(x, y, 0) = volume.at(x, y, z).value == 0 ? y : B.at(x, y - 1, 0);
			}
			F.at(x, volume.height() - 1, 0) = volume.at(x, volume.height() - 1, z).value == 0 ? volume.height() - 1 : MAX;
			for (int y = volume.height() - 2; y >= 0; y--) {
				F.at(x, y, 0) = volume.at(x, y, z).value == 0 ? y : F.at(x, y + 1, 0);
			}
		}

		for (int x = 0; x < volume.width(); x++) {
			for (int y = 0; y < volume.height(); y++) {
				LR.at(x, y, 0) = std::min(std::pow(x - L.at(x, y, 0), 2), std::pow(x - R.at(x, y, 0), 2));
				BF.at(x, y, 0) = std::min(std::pow(y - B.at(x, y, 0), 2), std::pow(y - F.at(x, y, 0), 2));
			}
		}

		for (int x = 0; x < volume.width(); x++) {
			for (int y = 0; y < volume.height(); y++) {

				if (volume.at(x, y, z).value == 0) {
					tEDT.at(x, y, z) = 0;
				}
				else {

					glm::vec3 n;
					if (y>0) n = glm::vec3(x, y-1, z);
					else if (x > 0) n = glm::vec3(x - 1, y, z);

					if ((x>0 || y>0) && tEDT.at(n.x, n.y, n.z) >= 0)
					{
						float r0 = std::sqrt( tEDT.at(n.x, n.y, n.z));

						float value = MAX;
						int layers[] = { r0 - 1, r0, r0 + 1 };
						int c = 0;
						for (int r : layers)// = y - r0 - 1; j < y + r0 + 1; j++) 
						{
							float tD = MAX;
							if (y - r >= 0) tD = LR.at(x, y - r, 0);
							if (y + r < volume.height()) tD = std::min(tD, LR.at(x, y + r, 0));
							if (x - r >= 0) tD = std::min(tD, BF.at(x - r, y, 0));
							if (x + r < volume.width()) tD = std::min(tD, BF.at(x + r, y, 0));

							if (tD < r * r) {
								c++;
								value = std::min(value, tD + r * r);
								if (value <= (r + 1) * (r + 1)) break;
							}

						}
						
						if (c == 0) {
							for (int j = 0; j < volume.height(); j++) {
								value = std::min(value, LR.at(x, j, 0) + (y - j) * (y - j));
							}
							//std::cout << value << " " << x << " " << y << " " << r0 << "\n";
						}
						tEDT.at(x, y, z) = value;


					}
					else {
						tEDT.at(x, y, z) = MAX;
						for (int j = 0; j < volume.height(); j++) {
							tEDT.at(x, y, z) = std::min(tEDT.at(x, y, z), LR.at(x, j, 0) + (y - j) * (y - j));
						}

					}


				}
			}
		}
	}
	p.set_value({ tEDT,index });
}



am::math::Mat3D<GridPoint> EDTSpaceFiller::buildVolume(std::vector<am::bio::Atom> atoms, std::unordered_map<std::string, float>& opts) {

	float scale = options::getOptionWithError(opts, "scaling_factor");
	float probe = options::getOptionWithError(opts, "probe_radius");
	float surface = options::getOptionWithError(opts, "surface");
	int n_threads = options::getOption(opts, "filling_threads", 1);


	AtomSpaceFiller filler;
	am::math::Mat3D<GridPoint> volume = filler.buildVolume(atoms, opts);
	opts["isovalue"] = 1;
	if (surface == options::MS) {
		opts["isovalue"] = probe * scale * probe * scale;

		/*std::promise<am::Mat3D<float>> p;
		auto f = p.get_future();
		auto th = std::thread(&func, std::move(p));
		th.join();
		auto m = f.get();
		std::cout << m.at(0,0,0) << "\n";*/

		std::vector<std::thread> threads;
		std::vector<std::future<struct EDTSpaceFiller::Partial>> futures;

		am::utils::Logger l("EDT");

		int range = volume.depth() / n_threads;
		for (int i = 0; i < n_threads; ++i) {
			std::promise<struct EDTSpaceFiller::Partial> p;
			auto f = p.get_future();

			threads.emplace_back(&func, std::move(p), volume, range * i, range * (i + 1), i);
			futures.push_back(std::move(f));
		}

		for (auto& thread : threads) {
			thread.join();
		}

		am::math::Mat3D<float> tEDT(volume.width(), volume.height(), volume.depth(), -1);
		
		for (auto& f : futures) {
			auto m = f.get();

			for (int z = range * m.index; z < range * (m.index + 1); z++) {
				for (int x = 0; x < volume.width(); x++) {
					for (int y = 0; y < volume.height(); y++) {
						tEDT.at(x, y, z) = m.tEDT.at(x, y, z);
					}
				}
			}
		}

		float MAX = INFINITY;
		am::math::Mat3D<float> EDT(volume.width(), volume.height(), volume.depth(), MAX);
		for (int x = 0; x < volume.width(); x++) {
			for (int y = 0; y < volume.height(); y++) {
				for (int z = 0; z < volume.depth(); z++) {
					
					if (volume.at(x, y, z).value == 0) {
						EDT.at(x, y, z) = 0;
						continue;
					}
					if (x > 0 || y > 0 || z > 0)
					{
						float r;

						if (x > 0) r = std::sqrt(EDT.at(x - 1, y, z)) + 1;
						else if (y > 0) r = std::sqrt(EDT.at(x, y - 1, z)) + 1;
						else if (z > 0) r = std::sqrt(EDT.at(x, y, z - 1)) + 1;

						float value = MAX;
						for (int j = 1; j <= r; j++) {
							if (z - j >= 0) {
								int i = z - j;
								value = std::min(value, ((z - i) * (z - i) + tEDT.at(x, y, i)));
							}
							if (z + j < volume.width()) {
								int i = z + j;
								value = std::min(value, ((z - i) * (z - i) + tEDT.at(x, y, i)));
							}
						}
						EDT.at(x, y, z) = value;
					}
					else {
						float value = MAX;
						for (int i = 0; i < volume.depth(); i++) {
							value = std::min(value, ((z - i) * (z - i) + tEDT.at(x, y, i)));
						}
						EDT.at(x, y, z) = value;
					}
					volume.at(x, y, z).value = EDT.at(x, y, z);
					//if (EDT.at(x, y, z) < (probe * scale) * (probe * scale)) volume.at(x, y, z).value = 0;
					//else volume.at(x, y, z).value = 1;

				}
			}
		}
	}

	return volume;
}