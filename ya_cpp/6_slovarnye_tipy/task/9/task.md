# FSM обслуживания самолёта

Реализуйте конечный автомат обслуживания самолёта после посадки с помощью `std::variant` и двойной диспетчеризации.

## Таблица переходов

| Состояние | Событие | Результат |
|---|---|---|
| `WaitingForArrival` | `PlaneLanded` | `Docking` |
| `Docking` | `GateConnected` | `DisembarkingPassengers` |
| `DisembarkingPassengers` | `PassengersExited` | `GroundServiceInProgress` |
| `GroundServiceInProgress` | `ServicesCompleted`, все флаги `true` | `GroundServiceFinished` |
| `GroundServiceInProgress` | `ServicesCompleted`, не все флаги `true` | Обновлённое `GroundServiceInProgress` |
| `GroundServiceInProgress` | `IncidentDetected` | `IncidentHandling` |
| `IncidentHandling` | `IncidentResolved` | Предыдущее `GroundServiceInProgress` |
| Любая другая пара | — | `std::logic_error` |

## Требования

1. Определите структуры событий и `AircraftEvent`.
2. Реализуйте все допустимые переходы в `AircraftStateVisitor`.
3. Добавьте универсальный fallback для недопустимых пар.
4. При `GateConnected` проверьте совпадение номера ворот.
5. Через `std::ranges::all_of` проверьте завершение всех сервисных работ.
6. При инциденте сохраните прогресс обслуживания, чтобы восстановить его после `IncidentResolved`.

## Прекод

```cpp
#include <algorithm>
#include <array>
#include <cassert>
#include <functional>
#include <ranges>
#include <stdexcept>
#include <string>
#include <variant>
#include <vector>

namespace state {

struct WaitingForArrival {};

struct Docking {
    std::string gateNumber;
};

struct DisembarkingPassengers {
    int passengerCount;
};

struct GroundServiceInProgress {
    bool refuelingDone;
    bool baggageUnloaded;
    bool cleaningDone;
};

struct IncidentHandling {
    std::string issueDescription;
    bool critical;
    GroundServiceInProgress previous;
};

struct GroundServiceFinished {};

} // namespace state

using AircraftState = std::variant<
    state::WaitingForArrival,
    state::Docking,
    state::DisembarkingPassengers,
    state::GroundServiceInProgress,
    state::IncidentHandling,
    state::GroundServiceFinished
>;

namespace event {

// Определите:
// PlaneLanded{gateNumber}
// GateConnected{gateNumber}
// PassengersExited{passengerCount}
// ServicesCompleted{refueling, baggage, cleaning}
// IncidentDetected{issueDescription, critical}
// IncidentResolved{}

} // namespace event

using AircraftEvent = std::variant<
    // Добавьте все события.
>;

namespace S = state;
namespace E = event;

class AircraftStateVisitor {
public:
    // Реализуйте допустимые переходы и fallback.
};

int main() {
    AircraftState currentState = S::WaitingForArrival{};

    std::vector<AircraftEvent> events = {
        E::PlaneLanded{"A12"},
        E::GateConnected{"A12"},
        E::PassengersExited{132},
        E::ServicesCompleted{true, true, false},
        E::IncidentDetected{"Утечка топлива", true},
        E::IncidentResolved{},
        E::ServicesCompleted{true, true, true},
    };

    for (const auto& event : events) {
        currentState = std::visit(
            AircraftStateVisitor{}, currentState, event
        );
    }

    assert(std::holds_alternative<S::GroundServiceFinished>(
        currentState
    ));
}
```

## Подсказки

- Каждый `operator()` посетителя должен возвращать `AircraftState`.
- После `GateConnected` можно создать `DisembarkingPassengers{0}`; фактическое число приходит в следующем событии.
- Для проверки работ соберите флаги в `std::array` и передайте `std::identity{}` в `std::ranges::all_of`.
- При незавершённых работах перенесите флаги события в новое состояние прогресса.
- В `IncidentHandling` сохраните прежний `GroundServiceInProgress`.
