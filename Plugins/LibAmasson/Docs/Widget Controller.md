*Why the need for widget controller*

## Widget Controller

*What is a widget controller*

*Its main functions to override*

*Make it observe an actor*

### Widget Controller Component

Widget Controller can be split into components just like an actor.
For this purpose, the Widget Controller Component class exists.
Abbreviated "Wcc" when subclassing it.

The Widget Controller has an array of components.
We can add one from a class using the method `AddComponent<MyWcc>("MyWcc")`.
That will add the component to the list and allow it to be retrieved using its name or its class.
This method should be used by overriding the `Construct` method from the widget controller.

```cpp
void UMyWidgetController::Construct()
{
	Super::Construct();

	MyWcc = AddComponent<UMyWcc>("MyWcc");
}
```

Note that the observed actor is not initialized yet so we can't fetch any data from it yet.
We should wait the call from the function `ObservedActorSet()` to create any observing behavior.

```cpp
void UMyWidgetController::ObservedActorSet()
{
	Super::ObservedActorSet();

	MyWcc->ObserveActor(GetObservedActor());
}
```

To get an existing component, we can fetch it in C++ with the method `GetComponent<MyWcc>()` or with other methods also usable from blueprint that all begin with `GetComponent[...]`

The Widget Controller Component should 

## Controllable User Widget


## Controller State broadcast

