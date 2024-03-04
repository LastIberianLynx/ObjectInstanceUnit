# ObjectInstanceUnit
In this exercise I made a Unit system with UObject and ISM architecture in mind.
UObject is spawned, added to the Array AllUnits, with its corresponding index, that is also the instance index.
On DestroyUnit(), I remove the instance and the array index by grabbing the last index properties and overwritting the unit that we want to remove, only then i remove the Last index.
This method makes it such that the we dont have to reorder the arrays or iterate through them when removing.
To test if its working I move the index in the middle forward, and Destroy it.
