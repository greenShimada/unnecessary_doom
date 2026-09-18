#include "doom/shader.h"
#include "doom/texture.h"
#include "glm/ext/vector_float2.hpp"

class SpriteRenderer
{
	public:
		SpriteRenderer(Shader &shader);
		~SpriteRenderer();

		void DrawSprite(
				Texture &texture, 
				glm::vec3 position, 
				glm::vec3 size = glm::vec3(10.0f, 10.0f, 10.0f), 
				float rotate = 0.0f, 
				glm::vec3 color = glm::vec3(1.0f)
			);

	private:
		Shader		shader;
		unsigned int	quadVAO;

		void initRenderData();
};
