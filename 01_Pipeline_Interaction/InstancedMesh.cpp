#include "InstancedMesh.h"
#include "RenderModule.h"

InstancedMesh::~InstancedMesh()
{
	for (Transform* t : instances) {
		delete(t);
	}
}

void InstancedMesh::Draw()
{
	Shader& shader = RenderModule::Get().GetShader();

	//todo refacto shader materials
	vertexArrayObject.Bind();
	for (Transform* instance : instances) {
		glm::mat4 modelMatrix = instance->GetModelMatrix();
		shader.SetUniformMatrix4fv("model_matrix", modelMatrix);
		//glBindVertexArray(m_vertexArrayObject);
		//texture.Bind();
		//vertexArrayObject.Bind();
		//glDrawElements(GL_TRIANGLES, m_numIndices, GL_UNSIGNED_INT, 0);
		glDrawElements(GL_TRIANGLES, indicesVertexBuffer.GetCount(), GL_UNSIGNED_INT, 0);
		//glDrawElementsBaseVertex(GL_TRIANGLES, m_numIndices, GL_UNSIGNED_INT, 0, 0);

		//glBindVertexArray(0);
	}
	vertexArrayObject.Unbind();
}

void InstancedMesh::AddInstance(glm::vec3 position, glm::quat rotation, glm::vec3 scale)
{
	Transform* newInstance = new Transform(parent);

	newInstance->SetPosition(position);
	newInstance->SetRotation(rotation);
	newInstance->SetScale(scale);
	instances.push_back(newInstance);
}

void InstancedMesh::AddInstance(glm::vec3 position, glm::vec3 eulerAngles, glm::vec3 scale)
{
	Transform* newInstance = new Transform(parent);

	newInstance->SetPosition(position);
	newInstance->SetRotation(eulerAngles);
	newInstance->SetScale(scale);
	instances.push_back(newInstance);
}
