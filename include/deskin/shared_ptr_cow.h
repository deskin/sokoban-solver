#ifndef SHARED_PTR_COW_H_
#define SHARED_PTR_COW_H_

#include <memory>

namespace deskin {

namespace copy_on_write {

template <typename T>
inline
std::shared_ptr<T> &
copy_shared(std::shared_ptr<T> &p)
{
	{
		std::shared_ptr<T> copy(std::make_shared<T>(*p));
		using std::swap;
		swap(p, copy);
	}

	return p;
}

template <typename T>
inline
std::shared_ptr<T> &
copy_if_shared(std::shared_ptr<T> &p)
{
	if (!p.unique()) {
		copy_shared(p);
	}

	return p;
}

} // namespace deskin::copy_on_write

} // namespace deskin

#endif // SHARED_PTR_COW_H_
