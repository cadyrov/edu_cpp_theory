# Ленивая загрузка профиля через `std::optional`

Перепишите `UserProfile`, заменив ручные флаги `isProfileLoaded_` и `hasHintWord_` на `std::optional`.

## Требования

- профиль загружается с сервера только при первом вызове `LoadProfile`;
- последующие вызовы возвращают уже загруженный объект;
- подсказка может отсутствовать или содержать пустую строку;
- `GetHintWordOrDefault` возвращает подсказку либо переданное значение;
- отдельные логические флаги использовать нельзя.

## Прекод

```cpp
#include <string>
#include <utility>

class UserProfile {
public:
    explicit UserProfile(std::string id)
        : userId_(std::move(id)) {}

    const ProfileData& LoadProfile() {
        if (!isProfileLoaded_) {
            profile_ = FetchProfileFromServer(userId_);
            isProfileLoaded_ = true;
        }
        return profile_;
    }

    void SetHintWord(std::string value) {
        hintWord_ = std::move(value);
        hasHintWord_ = true;
    }

    std::string GetHintWordOrDefault(
        const std::string& fallback
    ) const {
        return hasHintWord_ ? hintWord_ : fallback;
    }

private:
    std::string userId_;
    bool isProfileLoaded_ = false;
    ProfileData profile_;

    bool hasHintWord_ = false;
    std::string hintWord_;
};
```

## Подсказки

- Добавьте `#include <optional>`.
- Поля `profile_` и `hintWord_` сделайте опциональными.
- Проверить наличие значения можно через `if (profile_)`.
- После проверки доступ к объекту возможен через `*profile_`.
- Для подсказки используйте `value_or`.
