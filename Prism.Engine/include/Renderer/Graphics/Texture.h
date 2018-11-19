#pragma once
namespace Renderer {
	namespace Graphics {
		class Texture {
		public:
			Texture()=default;
			virtual void bind() = 0;
		};
	}
}