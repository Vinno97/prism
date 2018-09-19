#pragma once

#include <cstdio>
#include <tuple>
#include <vector>


namespace ECS {

	struct BaseComponent;
	typedef void *EntityHandle;
	typedef unsigned int(*ECSComponentCreateFunction)(std::vector<unsigned short> &memory, EntityHandle entity, BaseComponent *comp);
	typedef void(*ECSComponentFreeFunction)(BaseComponent *comp);

	struct BaseComponent
	{
	public:
		static unsigned int registerComponentType(ECSComponentCreateFunction createfn,
			ECSComponentFreeFunction freefn,
			size_t size);
		EntityHandle entity = nullptr;

		inline static ECSComponentCreateFunction getTypeCreateFunction(unsigned int id)
		{
			return std::get<0>((*componentTypes)[id]);
		}

		inline static ECSComponentFreeFunction getTypeFreeFunction(unsigned int id)
		{
			return std::get<1>((*componentTypes)[id]);
		}

		inline static size_t getTypeSize(unsigned int id)
		{
			return std::get<2>((*componentTypes)[id]);
		}

		inline static bool isTypeValid(unsigned int id)
		{
			return id < componentTypes->size();
		}

	private:
		static std::vector<std::tuple<ECSComponentCreateFunction, ECSComponentFreeFunction, size_t>> *componentTypes;
	};


	template <typename T>
	struct Component : public BaseComponent
	{
		static const ECSComponentCreateFunction CREATE_FUNCTION;
		static const ECSComponentFreeFunction FREE_FUNCTION;
		static const unsigned int ID;
		static const size_t SIZE;
	};

	template <typename ComponentT>
	unsigned int ECSComponentCreate(std::vector<unsigned short> &memory, EntityHandle entity, BaseComponent *comp)
	{
		unsigned int index = memory.size();
		memory.resize(index + ComponentT::SIZE);
		ComponentT *component = new (&memory[index]) ComponentT(*(Component *)comp);
		component->entity = entity;
		return index;
	}

	template <typename ComponentT>
	void ECSComponentFree(BaseComponent *comp)
	{
		ComponentT *component = (ComponentT *)comp;
		component->~Component();
	}

	template <typename T>
	const unsigned int Component<T>::ID(BaseComponent::registerComponentType(
		ECSComponentCreate<T>, ECSComponentFree<T>, sizeof(T)));

	template <typename T>
	const size_t Component<T>::SIZE(sizeof(T));

	template <typename T>
	const ECSComponentCreateFunction Component<T>::CREATE_FUNCTION(ECSComponentCreate<T>);

	template <typename T>
	const ECSComponentFreeFunction Component<T>::FREE_FUNCTION(ECSComponentFree<T>);

}