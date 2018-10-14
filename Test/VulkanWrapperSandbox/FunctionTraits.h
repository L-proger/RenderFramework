#pragma once
#include <functional>

template<class F>
struct FunctionTraits;

template<class R, class... Args>
struct FunctionTraits<R(Args...)>
{
	using ReturnType = R;

	static constexpr std::size_t Arity = sizeof...(Args);

	using AllArgs = std::tuple<Args...>;

	template <int N>
	struct ArgumentHelper
	{
		static_assert(N < Arity, "error: invalid parameter index.");
		using Type = typename std::tuple_element<N, std::tuple<Args...>>::type;
	};

	template <int N>
	using Argument = typename ArgumentHelper<N>::Type;
};

// function pointer
template<class R, class... Args>
struct FunctionTraits<R(*)(Args...)> : public FunctionTraits<R(Args...)>
{};


template<typename T>
struct RemoveFirstType
{
};

template<typename T, typename... Ts>
struct RemoveFirstType<std::tuple<T, Ts...>>
{
	typedef std::tuple<Ts...> type;
};

template<class T>
struct RemoveFirstArg {};

template<typename TResult, typename ... TArgs>
struct RemoveFirstArg<TResult(TArgs...)> {

	template<typename TResult1, typename T = void, typename ... TArgs1>
	struct TypeHelper {
		using type = TResult1(*)(TArgs1...);
	};
	using pointerType = typename TypeHelper<TResult, TArgs...>::type;
	using type = std::remove_pointer_t<pointerType>;
};

template<typename TResult, typename ... TArgs>
struct RemoveFirstArg<TResult(*)(TArgs...)> : RemoveFirstArg<TResult(TArgs...)> {};

template<typename T>
using RemoveFirstArgT = typename RemoveFirstArg<T>::type;


template<typename T>
struct LambdaHelper {};

template<typename R, typename ... Args>
struct LambdaHelper<R(Args...)> {
	using RawFunc = R(*)(VkDevice, Args...);
	static auto makeLambda(RawFunc func, VkDevice device) {
		return [func, device](Args... args) {
			return func(device, args...);
		};
	}
};