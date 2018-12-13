#pragma once
namespace Renderer
{
	namespace Graphics
	{
		class Texture
		{
		public:
			Texture() = default;
			virtual void bind(int target) = 0;
			virtual int getID() = 0;
		};
	}
}
