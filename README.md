# Feed Meow Meow
### *an Arduino project that facilitates the selective feeding of cats*
The problem is that we have two cats (I know, say no more :), Vladimiw (Mewie) needs fancy hypo-alergenic food. Ms. Pepperfreckles (Ms. P) can and will eat his fancy food, but we'd rather she stuck to the cheap stuff. 

Currently, the expensive food is dispensed via food-roller (a plastic bottle with a hole in the side, super-low-tech), which Vladimiw happily rolls around to get one kernal at a time, that's fine and it keeps him from snarfing his food, which triggers vomiting (sheesh cats!). The cheap food needs to be dispensed three times a day by a human to the whining Ms. P, who begins with the high-pitched meows hours ahead of schedule. If we were to leave the cheap food out, Mewie would eat it & we'd be cleaning up diarrhea (cats!).

The **Feed Meow Meow** device will take the responsibility away from the humans and thus reduce the ammount of grating meows we need to endure. It is my first Arduino project.

#### Talk through
*Meow-trigger*

1. Push and hold a button (LED acknowledges) to record a few seconds of the cat's meow.
2. That sound is anylized for pitch (or whatever makes sense in practice)), which is stored.
3. A mic listens for that meow-signature or something quite close to it.
4. When heard, a sensor looks for a sitting cat within a certain range...
5. ... which triggers a servo to rotate the food bowl cover plates to the open position.
6. The cat should bend down to eat now, this is sensed with a lower distance sensor & that the upper one senses nothing. Both sensors will have a corresponding LED to facilitate trouble-shooting.
7. if the cat doesn't bend down within 10 seconds, it closes.
8. if the cat does, it stays open until it senses the cat has sat up, at which point it immediately closes.
9. Neither closing nor opening will happen very quickly.
10. A protected button & app button will allow humans to trigger the opening and closing of the cover plates & allow the doors to be left open for cat-training and testing purposes. While the doors are locked open, an LED will light & blink to indicate what the code is doing door-wise.

*Bowl-filler*

1. The bowl will be connected to a reservoir via a covered cheute.
2. At the top of the cheute/bottom of the reservoir will be a flap or cup or something that releases food.
3. A sensor in the food bowl will check to see how full it is. 
4. At the same time, it will keep track of the ammout of food dispensed on the current day.
5. There will be dial on the back of the device or a selector in the app for the setting of the allowed maximum.
6. If the bowl is low & the ammount dispensed hasn't exceeded the allotted maximum, a motor/servo will be triggered to dispense more food.
7. It will dispense one unit then wait a moment (for food to finish falling) then check to see if either condition has been met before looping though again.
8. If it cycles thorough (say) 10 times and neither condition has been met, there is trouble and the humans will be alerted through blinking light and app alert.
9. A sensor in the reservoir will track the level of food in it and alert a low level via LED and app-alert.
10. A button will allow the humans to manually dispense more food via app & device itself.

*The app (a stretch-goal as this introduces the World of WiFi)*

1. Will show current reservoir level
2. Last 10 meow opening times
3. Allow a remote open/close via button
4. Allow a remote refill via button
5. Control the setting of allowed daily maximum
6. Display any alerts when things don't work right
