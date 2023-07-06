#include "am.h"

/*

unsigned int am::gfx::loadShader(const char* filename, GLenum shader_type) {
    QOpenGLExtraFunctions* f = QOpenGLContext::currentContext()->extraFunctions();

    GLuint shader_id = 0;
    std::ifstream file;
    long file_size = -1;
    GLchar* glsl_source;

    file.open(filename, std::ifstream::ate | std::ifstream::binary);
    file_size = file.tellg();

    file.clear();
    file.seekg(0);

    glsl_source = (char*)malloc(file_size + 1);

    //(long)fread(glsl_source, sizeof(char), file_size, file);
    file.read(glsl_source, file_size);

    glsl_source[file_size] = '\0';

    if (0 != (shader_id = f->glCreateShader(shader_type)))
    {
        const GLchar* src = glsl_source;
        f->glShaderSource(shader_id, 1, &src, NULL);
        f->glCompileShader(shader_id);

        GLenum ErrorCheckValue = f->glGetError();
        if (ErrorCheckValue != GL_NO_ERROR)
        {
            qDebug() << "ERROR: Could not compile the shaders: \n";
            exit(-1);
        }
    }
    else
        qDebug() << "ERROR: Could not create a shader.\n";

    file.close();
    return shader_id;

}

bool am::gfx::loadAssImp(const char* path, std::vector<am::gfx::Mesh*>& mymesh)
{

	Assimp::Importer importer;

	const aiScene* scene = importer.ReadFile(path, aiProcess_JoinIdenticalVertices | aiProcess_Triangulate | aiProcess_FlipUVs);
	if (!scene) {
		fprintf(stderr, importer.GetErrorString());
		getchar();
		return false;
	}
	const aiMesh* mesh;

	// Fill vertices positions
	int num_meshes = scene->mNumMeshes;  //Numero di oggetti che compongono il modello
	mymesh.resize(num_meshes);  //Faccio il resize di mymesh al numero di mesh che compongono l'oggetto

	for (unsigned int nm = 0; nm < num_meshes; nm++)
	{
		//Per ogni mesh dell'oggetto 
		mesh = scene->mMeshes[nm];
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

		aiColor3D color;
		float value;
		// Read mtl file vertex data

		if (aiReturn_SUCCESS == material->Get(AI_MATKEY_COLOR_AMBIENT, color))
		{
			//mymesh[nm].material->ambient = glm::vec3(color.r, color.g, color.b);
		}
		else
		{
			printf("Errore in ambientale \n");
		}

		if (aiReturn_SUCCESS == material->Get(AI_MATKEY_COLOR_DIFFUSE, color))
		{
			//mymesh[nm].material->diffuse = glm::vec3(color.r, color.g, color.b);
		}
		else
		{
			//mymesh[nm].material->diffuse = glm::vec3(1.0, 0.2, 0.1);
		}

		if (aiReturn_SUCCESS == material->Get(AI_MATKEY_COLOR_SPECULAR, color))
		{
			//mymesh[nm].material->specular = glm::vec3(color.r, color.g, color.b);
		}

		else
		{
			printf("Errore in specular \n");
			//mymesh[nm].material->specular = glm::vec3(0.5, 0.5, 0.5);
		}
		if (aiReturn_SUCCESS == material->Get(AI_MATKEY_SHININESS_STRENGTH, value))
		{
			//mymesh[nm].material->shininess = value;
		}
		else
		{
			//printf("Errore in shininess \n");
			//mymesh[nm].material->shininess = 50.0f;

		}

		// http://assimp.sourceforge.net/lib_html/structai_material.html

		std::vector<am::gfx::Vertex> verts;
		for (unsigned int i = 0; i < mesh->mNumVertices; i++) {

			aiVector3D pos = mesh->mVertices[i];
			verts.push_back({{ pos.x, pos.y, pos.z, 1.0f }, { 1,1,1,1 }});
			//mymesh[nm].vertici.push_back(glm::vec3(pos.x, pos.y, pos.z));

		}

		// Fill vertices texture coordinates

		for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
			//mymesh[nm].texCoords.push_back(glm::vec2(0.0, 0.0));
			//mymesh[nm].colori.push_back(glm::vec4(1.0, 0.0, 0.0, 1.0));


		}

		// Fill vertices normals

		for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
			aiVector3D n = mesh->mNormals[i];
			//mymesh[nm].normali.push_back(glm::vec3(n.x, n.y, n.z));
		}


		// Fill face indices
		std::vector<unsigned int> inds;
		for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
			// Assume the model has only triangles.
			//mymesh[nm].indici.push_back(mesh->mFaces[i].mIndices[0]);
			//mymesh[nm].indici.push_back(mesh->mFaces[i].mIndices[1]);
			//mymesh[nm].indici.push_back(mesh->mFaces[i].mIndices[2]);
			inds.push_back(mesh->mFaces[i].mIndices[0]);
			inds.push_back(mesh->mFaces[i].mIndices[1]);
			inds.push_back(mesh->mFaces[i].mIndices[2]);

		}

		mymesh[nm] = new am::gfx::Mesh(verts, inds, GL_TRIANGLES);

	}
	return true;
}


typedef CGAL::Exact_predicates_inexact_constructions_kernel Kernel;
typedef Kernel::Point_3  Point_3;

am::gfx::Mesh* am::gfx::loadMeshFromFile(const char* filename) {

	CGAL::Surface_mesh<Point_3> m;
	std::ifstream in(filename);
	in >> m;

	std::vector<am::gfx::Vertex> verts;
	for (CGAL::Surface_mesh<Point_3>::Vertex_index vd : m.vertices()) {
		am::gfx::Vertex v = {
			{
				(float)m.point(vd).x() ,
				(float)m.point(vd).y() ,
				(float)m.point(vd).z() ,
				1.0f
			},
			{0,1,0,1} };
		verts.push_back(v);

	}

	std::vector<GLuint> inds(m.number_of_faces() * 3);
	for (CGAL::Surface_mesh<Point_3>::Face_index fd : m.faces()) {
		for (CGAL::Surface_mesh<Point_3>::Vertex_index vd : m.vertices_around_face(m.halfedge(fd))) {
			inds.push_back(vd);
		}
	}
	am::gfx::Mesh* mesh = new Mesh(verts, inds, GL_POINTS);
	return mesh;
}
*/