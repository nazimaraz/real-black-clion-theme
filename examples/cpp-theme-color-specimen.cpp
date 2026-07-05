// Real Black C++ color specimen
// Open this file in CLion to inspect keyword, type, variable, function,
// template, macro, literal, punctuation, and diagnostic colors.

export module real_black.specimen;
import <array>;
import <compare>;
import <concepts>;
import <coroutine>;
import <cstddef>;
import <cstdint>;
import <exception>;
import <initializer_list>;
import <memory>;
import <new>;
import <stdexcept>;
import <string>;
import <type_traits>;
import <utility>;
import <vector>;

#define REAL_BLACK_STRINGIFY_IMPL(value) #value
#define REAL_BLACK_STRINGIFY(value) REAL_BLACK_STRINGIFY_IMPL(value)
#define REAL_BLACK_REPEAT(count, expression) \
    for (auto index = 0; index < (count); ++index) { expression; }

#if defined(__cpp_consteval) && !defined(REAL_BLACK_DISABLED)
#  pragma message("Real Black specimen: preprocessor directive color")
#elif defined(__clang__)
#  warning "Real Black specimen warning color"
#else
#  error "Real Black specimen error color"
#endif

namespace real_black::specimen {

using std::size_t;
using byte = unsigned char;
typedef long legacy_long;

extern int extern_counter;
constinit inline int global_counter = 42;
thread_local static volatile int tls_register_sink = 0;

alignas(64) struct alignas(16) AlignedBlock final {
public:
    explicit constexpr AlignedBlock(int initial) noexcept
        : value(initial), label(u8"aligned") {}

    auto operator<=>(const AlignedBlock&) const = default;
    auto operator+=(int delta) noexcept -> AlignedBlock&;
    auto draw() const -> void;

protected:
    mutable int cache = 0;

private:
    int value;
    const char8_t* label;
};

auto AlignedBlock::operator+=(int delta) noexcept -> AlignedBlock& {
    this->value += delta;
    return *this;
}

auto AlignedBlock::draw() const -> void {
    auto ChartRenderer = value;
    (void)ChartRenderer;
}

class ChartRenderer {
public:
    ChartRenderer() = default;
    ChartRenderer(const ChartRenderer&) = delete;
    ChartRenderer(ChartRenderer&&) noexcept = default;
    virtual ~ChartRenderer() = default;

    auto draw() const -> void;
    virtual auto render_frame(double seconds, const std::string& title) -> std::size_t = 0;
};

auto ChartRenderer::draw() const -> void {
    auto local_auto = 1;
    const auto constant_auto = local_auto + 2;
    constexpr auto compile_time_auto = 3;
    (void)constant_auto;
    (void)compile_time_auto;
}

struct DerivedRenderer final : public ChartRenderer {
    auto render_frame(double seconds, const std::string& title) -> std::size_t override {
        if (title.empty() or seconds < 0.0) {
            return 0U;
        } else if (seconds > 60.0 and not title.empty()) {
            return static_cast<std::size_t>(seconds);
        }
        return title.size();
    }
};

enum class RenderMode : std::uint8_t {
    Fast,
    Accurate,
    Debug = 0xFF
};

union PackedValue {
    int as_int;
    float as_float;
    char bytes[sizeof(double)];
};

template <typename T>
concept Drawable = requires(T object, double dt) {
    { object.draw() } -> std::same_as<void>;
    { object.render_frame(dt, std::string{}) } -> std::convertible_to<std::size_t>;
};

template <class T, std::size_t Count>
requires (Count > 0)
struct Buffer {
    using value_type = T;
    static constexpr std::size_t size = Count;

    std::array<T, Count> items{};

    template <typename Callback>
    constexpr auto for_each(Callback&& callback) & -> void {
        for (auto& item : items) {
            callback(item);
        }
    }
};

template <Drawable Renderer>
export constexpr auto render_all(Renderer& renderer) noexcept(noexcept(renderer.draw())) -> std::size_t {
    renderer.draw();
    return renderer.render_frame(1.0, "frame");
}

consteval auto compile_time_answer() -> int {
    return 40 + 2;
}

constexpr auto constexpr_answer = compile_time_answer();
static_assert(constexpr_answer == 42, "constexpr/static_assert colors");

auto literal_samples() -> void {
    bool truth = true;
    bool lie = false;
    char ascii = 'A';
    wchar_t wide = L'W';
    char8_t utf8 = u8'x';
    char16_t utf16 = u'x';
    char32_t utf32 = U'x';
    signed int signed_value = -7;
    short small = -1;
    unsigned long long huge = 1'000'000ULL;
    float f = 1.0f;
    double d = 2.0;
    long double ld = 3.0L;
    void* nullish = nullptr;

    auto raw = R"(raw\nstring)";
    auto escaped = "tab\tnewline\nquote\"";
    auto formatted = REAL_BLACK_STRINGIFY(escaped);

    (void)truth;
    (void)lie;
    (void)ascii;
    (void)wide;
    (void)utf8;
    (void)utf16;
    (void)utf32;
    (void)signed_value;
    (void)small;
    (void)huge;
    (void)f;
    (void)d;
    (void)ld;
    (void)nullish;
    (void)raw;
    (void)formatted;
}

auto casts_and_type_traits(void* raw, const AlignedBlock* block) -> void {
    auto as_block = static_cast<AlignedBlock*>(raw);
    auto same_block = const_cast<AlignedBlock*>(block);
    auto maybe_renderer = dynamic_cast<const ChartRenderer*>(reinterpret_cast<const ChartRenderer*>(block));
    auto name = typeid(*block).name();
    decltype(sizeof(AlignedBlock)) byte_count = sizeof(AlignedBlock);

    (void)as_block;
    (void)same_block;
    (void)maybe_renderer;
    (void)name;
    (void)byte_count;
}

auto control_flow(RenderMode mode, int value) -> int {
    register int legacy_register = value;

    switch (mode) {
        case RenderMode::Fast:
            break;
        case RenderMode::Accurate:
            legacy_register += 1;
            [[fallthrough]];
        default:
            legacy_register += 2;
            break;
    }

    for (int i = 0; i < 3; ++i) {
        if (i == 1) {
            continue;
        }
        legacy_register += i;
    }

    do {
        legacy_register--;
    } while (legacy_register > 10);

    while (legacy_register < 0) {
        goto recover;
    }

recover:
    try {
        if (legacy_register < 0) {
            throw std::runtime_error("negative value");
        }
    } catch (const std::exception& error) {
        return static_cast<int>(error.what()[0]);
    }

    return legacy_register;
}

auto operators_and_alternative_tokens(int left, int right) -> int {
    auto result = (left bitand right) bitor (left xor right);
    result and_eq 0xFF;
    result or_eq 0x10;
    result xor_eq 0x01;

    if (compl result not_eq 0 and (left <=> right) != 0) {
        return result;
    }

    return left + right - result * 2 / 3 % 5;
}

template <typename T>
class SmartBox {
public:
    friend auto operator==(const SmartBox&, const SmartBox&) -> bool = default;

    explicit SmartBox(T value) : value_(new T(std::move(value))) {}
    ~SmartBox() { delete value_; }

    auto operator*() const -> const T& { return *value_; }
    auto operator->() const -> const T* { return value_; }

private:
    T* value_;
};

struct Awaitable {
    auto await_ready() const noexcept -> bool { return false; }
    auto await_suspend(std::coroutine_handle<>) const noexcept -> void {}
    auto await_resume() const noexcept -> int { return 7; }
};

struct Task {
    struct promise_type {
        auto get_return_object() -> Task { return {}; }
        auto initial_suspend() noexcept -> std::suspend_never { return {}; }
        auto final_suspend() noexcept -> std::suspend_never { return {}; }
        auto return_value(int) noexcept -> void {}
        auto unhandled_exception() -> void {}
    };
};

auto coroutine_keywords() -> Task {
    co_yield 1;
    auto value = co_await Awaitable{};
    co_return value;
}

template <typename... Args>
auto lambda_and_pack(Args&&... args) -> std::size_t {
    auto visitor = [count = sizeof...(Args)]<typename Value>(Value&& value) mutable -> std::size_t {
        ++count;
        return count + sizeof(Value) + alignof(Value);
    };

    return (visitor(std::forward<Args>(args)) + ... + 0U);
}

[[nodiscard("inspect return color")]]
auto attributes_and_noexcept(int value) noexcept -> int {
    [[maybe_unused]] auto unused_value = value;
    return value;
}

asm("nop");

} // namespace real_black::specimen
