# Feed Meow Meow
### *an Arduino project that facilitates the selective feeding of cats*
The problem is that we have two cats (I know, say no more :), Vladimiw (Mewie) needs fancy hypo-allergenic food. Ms. Pepperfreckles (Ms. P) can and will eat his fancy food, but we'd rather she stuck to the cheap stuff. 

Currently, the expensive food is dispensed via food-roller (a plastic bottle with a hole in the side, super-low-tech), which Vladimiw happily rolls around to get one kernel at a time, that's fine and it keeps him from snarfing his food, which triggers vomiting (sheesh cats!). The cheap food needs to be dispensed three times a day by a human to the whining Ms. P, who begins with the high-pitched meows hours ahead of schedule. If we were to leave the cheap food out, Mewie would eat it & we'd be cleaning up diarrhea (cats!).

The **Feed Meow Meow** device will take the responsibility away from the humans and thus reduce the amount of grating meows we need to endure. It is my first Arduino project. __track my progress by visiting my blog at [puzzleinmotion.com](http://www.puzzleinmotion.com/new-blog)!__

Note: the original plan was to connect a microphone to the device so the cat could meow open the doors, but it was determined that the pitches of their respective meows were too close for that to be a reliable bio-metric without using someone else's fancy voice-recognition software. ~~The cats have different enough weights that this seems like a more reasonable way to determine which cat is heading in for more food.~~ Oops! Their weights are actually too close it turns out (foiled again!). The next plan involves image capture.

#### Talk through
*Meow-Meow Trigger*

1. A cat will step onto a scaled platform in order to access the covered food-bowl.
2. The scale will register that a cat-weight is present and signal the camera to take a lighted picture of the cat's flank.
3. The color of the pixels from the low resolution image will be averaged to deterine which cat's fur it's looking at.
5. If the correct cat is present, a servo to rotate the food bowl cover plates to the open position.
6. A selected portion of food will be dropped into the bowl (see 'Bowl-Filler' below).
6. The door will remain open as long as the cat remains on the scale.
7. Walls on either side of the bowl and the scale platform will prevent the other cat from squeezing in to feeding position without also stepping on the scale.
8. If the there is a large increase in the weight registered, it means the second cat is trying to get in & a buzzer near the end of the scale will briefly sound.
9. If the weight doesn't drop back to one-cat level within 3 seconds, the door will close. It will reopen if the weight goes back to one-cat level and the fur is a match.
8. When the cat walks away, the lid immediately closes and the cat's weight is sent to the database for record-keeping.
9. Neither closing nor opening will happen very quickly.
10. A protected button & app button will allow humans to trigger the opening and closing of the door.

*Bowl-Filler*

1. A food hopper will funnel into a 1" PVC tube containing a 1" steel auger.
2. This will lead to the cylinder containing food bowl.
5. There will be a place on the app to specify the size of the food portion to be dispensed.
6. Immediately after the door has opened, the specified portion will be distributed. Portions are measured in the number of rotations the auger has completed.
10. A button will allow the humans to manually dispense more food via app & device itself.
11. A sensor at the top of the food hopper will sense the distance to the top of the food pile within and report to the app and a series of LED lights on the side of the reservoir when it's getting low. 

*The App*

1. Will show current reservoir level
2. Last 10 feeding times
3. Last 10 cat weights 
4. Last 10 feeding amounts
3. Allow a remote open/close via button
4. Allow a remote refill via button
5. Allow the setting of portions
6. Display any alerts when things don't work right
