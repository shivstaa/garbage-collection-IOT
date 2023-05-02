# lahacksapp
Garbage classification and collection IOT Project Created for LAHacks
Contains: 
- Garbage controller (C script): Script that connects to microcontroller and implements bluetooth to determine whether to open the trash bin or the recyclables.
- Garbage AI Classification (Python script): Script that accesses video camera to determine whether the item detected is trash or recyclable and sends open or close bit via bluetooth serialization; Collects and sends metrics to Firebase for Mobile App to access.
- Mobile App (React Native): App that accesses Firebase to display metrics for trash and recyclables collected, alongside other information. 
