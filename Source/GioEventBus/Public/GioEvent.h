// Copyright MiddleMast. All rights reserved

#pragma once

#include "GioEvent.generated.h"

/**
 * @brief Helper class to simplify creation of new event listeners. Use one of the static creation methods of this type
 * when registering listeners to the event bus. For example:
 * <br><br>
 * TGioEventDelegate<FSomeEvent>::CreateLambda([](FSomeEvent Event){ Event Received Here! })
 * <br><br>
 * or
 * <br><br>
 * TGioEventDelegate<FSomeEvent>::CreateRaw(&MyObject, &MyClass::HandleEvent)
 */
template <typename TEvent>
class TGioEventDelegate : public TDelegate<void(TEvent)> {};

/**
 * @brief A base event structure to inherit from. Technically any USTRUCT will work as an event, but it's useful to have
 * a common ancestor to keep track of all events defined in the project (using your IDE's "find all derived symbols"
 * action, for example).
 */
USTRUCT()
struct FGioEvent
{
	GENERATED_BODY()
};
