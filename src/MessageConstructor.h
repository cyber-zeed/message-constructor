#ifndef MESSAGE_CONSTRUCTOR_H
#define MESSAGE_CONSTRUCTOR_H

#include <stdint.h>
#include <utility>

#ifdef ARDUINO
#include <Arduino.h>
#else
#include <chrono>
#include <iomanip>
#include <sstream>
#include <string>
#include <type_traits>
#endif

class MessageConstructor {
public:
#ifdef ARDUINO
    using StringType = String;
#else
    using StringType = std::string;
#endif

    StringType constructMessage() const {
        return constructMessageAt(nowMilliseconds());
    }

    template<typename... Args>
    StringType constructMessage(Args&&... args) const {
        return constructMessageAt(nowMilliseconds(), std::forward<Args>(args)...);
    }

    template<typename... Args>
    StringType constructMessageAt(uint64_t timestampMs, Args&&... args) const {
        StringType message = prefix(timestampMs);
        appendAll(message, std::forward<Args>(args)...);
        message += "#@";
        return message;
    }

private:
    static uint64_t nowMilliseconds() {
#ifdef ARDUINO
        return static_cast<uint64_t>(millis());
#else
        using Clock = std::chrono::steady_clock;
        static const Clock::time_point start = Clock::now();
        return static_cast<uint64_t>(
            std::chrono::duration_cast<std::chrono::milliseconds>(Clock::now() - start).count());
#endif
    }

    static StringType prefix(uint64_t timestampMs) {
#ifdef ARDUINO
        return String("@#<") + String(static_cast<unsigned long>(timestampMs)) + ">#";
#else
        return std::string("@#<") + std::to_string(timestampMs) + ">#";
#endif
    }

    static StringType escape(const StringType& value) {
        StringType output;
#ifdef ARDUINO
        output.reserve(value.length());
        for (size_t i = 0; i < value.length(); ++i) {
            const char c = value[i];
#else
        output.reserve(value.size());
        for (char c : value) {
#endif
            if (c == '\\' || c == '&' || c == '#') {
                output += '\\';
            }
            output += c;
        }
        return output;
    }

#ifdef ARDUINO
    static StringType toString(const String& value) { return value; }
    static StringType toString(const char* value) { return value ? String(value) : String(); }
    static StringType toString(char value) { return String(value); }
    static StringType toString(bool value) { return value ? "1" : "0"; }

    template<typename T>
    static StringType toString(const T& value) { return String(value); }
#else
    static StringType toString(const std::string& value) { return value; }
    static StringType toString(const char* value) { return value ? std::string(value) : std::string(); }
    static StringType toString(char value) { return std::string(1, value); }
    static StringType toString(bool value) { return value ? "1" : "0"; }

    template<typename T>
    static typename std::enable_if<std::is_integral<T>::value && !std::is_same<T, char>::value && !std::is_same<T, bool>::value, StringType>::type
    toString(T value) {
        return std::to_string(value);
    }

    template<typename T>
    static typename std::enable_if<std::is_floating_point<T>::value, StringType>::type
    toString(T value) {
        std::ostringstream stream;
        stream << std::setprecision(6) << std::defaultfloat << value;
        return stream.str();
    }
#endif

    static void appendAll(StringType&) {}

    template<typename T, typename... Args>
    static void appendAll(StringType& message, T&& value, Args&&... args) {
        message += '&';
        message += escape(toString(std::forward<T>(value)));
        appendAll(message, std::forward<Args>(args)...);
    }
};

#endif
