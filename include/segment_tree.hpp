//
// Created by Andrey Solovyev on 22.09.2024.
//

#pragma once

#include <type_traits>
#include <concepts>
#include <vector>
#include <optional>
#include <cstddef>

namespace containers {

	template <typename T, typename Func>
	requires (std::default_initializable<Func> && std::is_nothrow_invocable_r_v<T, Func, T, T>)
	class segment_tree final {
	public:

		segment_tree() = default;

		segment_tree(std::vector<T> const& input) requires std::default_initializable<T> {
			build(input);
		}

		segment_tree(std::vector<T> const &input, T default_value) {
			build(input, default_value);
		}

		segment_tree(std::vector<T> const& input, Func f) requires std::default_initializable<T>
		: func(f)
		{
			build(input);
		}

		segment_tree(std::vector<T> const &input, T default_value, Func f)
		: func(f)
		{
			build(input, default_value);
		}

		void build (std::vector<T> const& input) requires std::default_initializable<T>
		{
			if (input.empty()) {
				return;
			}
			sz = input.size();
			t.resize(4 * sz);
			build_(input, root, 0, sz - 1);
		}

		void build(std::vector<T> const &input, T default_value)
		{
			if (input.empty()) {
				return;
			}
			sz = input.size();
			t.resize(4 * sz, default_value);
			build_(input, root, 0, sz - 1);
		}

		std::optional<T> query (std::size_t l, std::size_t r) const noexcept {
			if (!is_ok_bounds(l, r)) {
				return std::nullopt;
			}
			return query_(root, 0, sz - 1, l, r);
		}

		bool update (T val, std::size_t pos) noexcept {
			if (!is_ok_bounds(pos)) {
				return false;
			}
			update_(root, 0, sz - 1, val, pos);
			return true;
		}

	private:
		Func func;
		std::vector<T> t;
		std::size_t sz;
		std::size_t const root{0};

		std::size_t left(std::size_t idx) const noexcept {
			return idx * 2 + 1;
		}

		std::size_t right (std::size_t idx) const noexcept {
			return idx * 2 + 2;
		}

		template<typename... Idxs>
		requires ((std::same_as<Idxs, std::size_t> || std::is_nothrow_convertible_v<Idxs, std::size_t>), ...)
		bool is_ok_bounds(Idxs &&... idxs) const noexcept {
			bool res {true};
			((res = res && idxs < sz), ...);
			return res;
		}

		void build_ (std::vector<T> const& s, std::size_t v, std::size_t tl, std::size_t tr) noexcept {
			if (tl == tr) {
				t[v] = s[tl];
				return;
			}
			std::size_t tm = tl + (tr - tl) / 2;
			build_(s, left(v), tl, tm);
			build_(s, right(v), tm + 1, tr);
			t[v] = func(t[left(v)], t[right(v)]);
		}

		void update_(std::size_t v, std::size_t tl, std::size_t tr, T const& val, std::size_t pos) noexcept {
			if (tl == tr) {
				t[v] = val;
				return;
			}
			std::size_t tm = tl + (tr - tl) / 2;
			if (pos <= tm) {
				update_(left(v), tl, tm, val, pos);
			}
			else {
				update_(right(v), tm + 1, tr, val, pos);
			}
			t[v] = func(t[left(v)], t[right(v)]);
		}

		std::optional<T> query_(std::size_t v, std::size_t tl, std::size_t tr, std::size_t l, std::size_t r) const noexcept {
			if (l > r) {
				return std::nullopt;
			}
			if ((tr == tl) || (tl == l && tr == r)) {
				return t[v];
			}

			std::size_t tm = tl + (tr - tl) / 2;
			std::optional<T> const left_subtree_res
					{query_(left(v), tl, tm, l, std::min(tm, r))};
			std::optional<T> const right_subtree_res
					{query_(right(v), tm + 1, tr, std::max(tm + 1, l), r)};

			if (left_subtree_res && right_subtree_res) {
				return func(left_subtree_res.value(), right_subtree_res.value());
			} else if (!left_subtree_res && right_subtree_res) {
				return right_subtree_res;
			} else if (left_subtree_res && !right_subtree_res) {
				return left_subtree_res;
			} else {
				return std::nullopt;
			}
		}
	};
}//!namespace containers
