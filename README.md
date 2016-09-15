# piDrummer

piDrummer is a DIY drum trigger device. it uses an Arduino and some basic components to get the signal from your pads (AKA triggers) and send them to a Raspberry Pi 3.

A Raspberry Pi 3 is used to play sounds according to the triggers you hit. 

Thanks to CPU power of a such board computer (4x1.2 Ghz), it is possible to play the best sound quality !

The rPi is also driving an ILI9341 TFT screen (320x240 pixels, can be found as cheap as 5$ on ebay ) and displays an interface that allows you to set up your different drum kits, the volume, sound effects (reverb, equalizer, etc...), and map each trigger to an instrument.

The goal is also to build an embedded linux, with the smallest possible kernel, allowing for very small boot time !

# piDrummer (Version Française)

piDrummer est un module de batterie électronique à fabriquer soi-même.

Il utilise un module Arduino et quelques composants pour récupérer le signal depuis les PADS (aussi appelés Triggers), et envoie ces informations à une carte Raspberry Pi 3.

La carte est alors utilisée pour jouer les sons en fonction des coups donnés.

Grâce à la puissance de calcul disponible sur la carte (4x1.2 Ghz), un rendu sonore de haute qualité est possible !

La carte rPi est aussi utilisée pour piloter un afficheur TFT (320x240 à base de puce ILI9341, qu'on peut acheter sur Ebay pour moins de 5€) afin de régler et choisir vos différents kits, le volume, les effets sonores (reverb, équaliseur, etc...) et mapper chaque trigger à un instrument.

Le but du projet est aussi de monter un système linux embarqué (linux Embedded) avec un noyau le plus léger possible, et un temps de démarrage le plus faible possible !
