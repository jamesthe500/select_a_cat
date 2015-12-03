# Feed Meow Meow
### *an Arduino project that facilitates the selective feeding of cats*
The problem is that we have two cats (I know, say no more :), Vladimiw (Mewie) needs fancy hypo-allergenic food. Ms. Pepperfreckles (Ms. P) can and will eat his fancy food, but we'd rather she stuck to the cheap stuff. 

Currently, the expensive food is dispensed via food-roller (a plastic bottle with a hole in the side, super-low-tech), which Vladimiw happily rolls around to get one kernel at a time, that's fine and it keeps him from snarfing his food, which triggers vomiting (sheesh cats!). The cheap food needs to be dispensed three times a day by a human to the whining Ms. P, who begins with the high-pitched meows hours ahead of schedule. If we were to leave the cheap food out, Mewie would eat it & we'd be cleaning up diarrhea (cats!).

The **Feed Meow Meow** device will take the responsibility away from the humans and thus reduce the amount of grating meows we need to endure. It is my first Arduino project.

Note: the original plan was to connect a microphone to the device so the cat could meow open the doors, but it was determined that the pitches of their respective meows were too close for that to be a reliable bio-metric without using someone else's fancy voice-recognition software. The cats have different enough weights that this seems like a more reasonable way to determine which cat is heading in for more food.

#### Talk through
*Meow-Meow Trigger*

1. A cat will step onto a scaled platform in order to access the covered food-bowl.
2. The scale will register the weight and check to see that it is within a range of the last recorded weight.
5. If so, a servo to rotate the food bowl cover plates to the open position.
6. One portion of food will be dropped into the bowl if it is supposed to (see 'Bowl-Filler' below).
6. The doors will remain open as long as the cat remains on the scale.
7. Walls on either side of the bowl and the scale platform will prevent the other cat from squeezing in to feeding position without also stepping on the scale.
8. If the there is a large increase in the weight registered, it means the second cat is trying to get in & a buzzer near the end of the scale will briefly sound.
9. If the weight doesn't drop back to one-cat level within 3 seconds, the bowl will be re-covered. The lid will reopen if the weight goes back to one-cat level.
8. When the cat walks away, the lid immediately closes and the last stable weight is sent to the database as the standard for the next feeding.
9. Neither closing nor opening will happen very quickly.
10. A protected button & app button will allow humans to trigger the opening and closing of the cover plates & allow the doors to be left open for cat-training and testing purposes. While the doors are locked open, an LED will light to indicate what the code is doing door-wise.

*Bowl-Filler*

1. A food reservoir will lead to a chute that funnels to just above the food bowl.
2. At the top of the chute/bottom of the reservoir will be a hard sphere with a portion cut off, such that it can work as a sort of cup. Through the sphere will be a rod connected to a VCR motor. Its standard position will be opening up, receiving food.
3. A pressure plate below the food bowl will check to see how full it is. 
5. There will be dial on the back of the device for the setting of each opening's ration.
6. Immediately after the doors have opened, if the bowl is light enough, the device will dispense the number of portions specified by the dial. 
7. Between each dispensing it will check the bowl weight to guard against overfilling.
8. The pressure sensor will check to see that there has been a positive change in the pressure, thus indicating food was dispensed. If not, the humans will be alerted with a blinking light & app alert as something has gone wrong. 
10. A button will allow the humans to manually dispense more food via app & device itself.
11. A sensor at the top of the food reservoir will sense the distance to the top of the food pile within and report to the app and a series of LED lights on the side of the reservoir. 

*The app (a stretch-goal as this introduces the Wide World of WiFi)*

1. Will show current reservoir level
2. Last 10 feeding times
3. Last 10 cat weights 
4. Last 10 feeding amounts
3. Allow a remote open/close via button
4. Allow a remote refill via button
6. Display any alerts when things don't work right

