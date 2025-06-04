#ifndef QUEUE_H
#define QUEUE_H
#include <utility>

#include "List.h"
namespace sdf
{
	template<class T>
	class Queue
	{
	public:
		Queue() = default;
		~Queue() = default;

		void push(T&& data)
		{
			list_.push_back(std::forward<T>(data));
		}
		void pop(T&& data)
		{
			list_.pop_front();
		}
		[[nodiscard]] std::size_t size() const
		{
			return list_.size();
		}
		bool empty() const
		{
			return list_.empty();
		}

		auto begin() {
			return list_.begin();
		}

		auto end() {
			return list_.end();
		}
		

	private:
		List<T> list_;
	};
}

#endif // QUEUE_H
