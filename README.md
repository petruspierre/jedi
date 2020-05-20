# Jedi

You can see the informations more detailed [clicking here](https://github.com/petruspierre/jedi/blob/master/diario.pdf) but it is in portuguese.

## Introduction

Jedi was the name that me and my team choose for this robot that have these two blue leds on the front that looks like a lightsaber for Brazilian Robotics Olympics.<br>
![Jedi](https://i.ibb.co/yS6yZYs/JEdi.png)

First of all we need to know what is the Brazilian Robotics Olympics [(OBR)](http://www.obr.org.br).
Well, picking the description of the competition in the site we have:

> *The Brazilian Robotics Olympics (OBR) is one of the Brazilian Scientific Olympics that uses the theme of robotics.*

![Field](https://s2.glbimg.com/_Y6ec6nmPBj_usq_d6vqMhAfE_E=/0x0:1024x768/984x0/smart/filters:strip_icc()/i.s3.glbimg.com/v1/AUTH_59edd422c0c84a879bd37670ae4f538a/internal_photos/bs/2019/b/u/3nAP84SEW3vwy6GaHlaQ/20181109-115801-1024x768.jpg)

There is two modalities in this Olympics, but we will focus in the Practical one.

In the Practical modality we have an challenge very similar to Robocup Line Rescue. So we have an field with some black and green tape and the robot should pass through the path and at the final rescue some balls that represents victims of a disaster.

## Hardware

We started by the *batteries* that we would use in the robot. So we choose 4 notebook cells of Lithium battery for it. And for the charge were TP4056 controllers.

Then we did the circuit board that would have the 7 TCRT5000 we used to follow the black line and read the green squares.<br>
We did some prototypes. The first one that we made using Fritzing is below:

![first_circuit](https://i.ibb.co/4fbzfy3/first-circuit.png)

> *Note that was the first PCB board we have ever made*

and the **definitive one** using ARES Proteus 7:

![last_circuit](https://i.ibb.co/DMqZHL3/last-circuit.png)
![board](https://i.ibb.co/HXx3nh4/board.png)

And the final circuit

![circuit](https://i.ibb.co/rv3LMnM/circuit.png)

## Line follower logic

![logic](https://i.ibb.co/J5j4rjp/logic.png)

You can find the implementation [here](https://github.com/petruspierre/jedi/blob/master/nacional/nacional.ino), but it is basically the "ifs" calling the functions that handle with each of these situations.

## Rescue logic

For the rescue is there is almost none sensor reading, just motor actions being executed, so we did some schemes like that:

![rescue](https://i.ibb.co/M8MVtD2/rescue.png)

You can see the program clicking [here](https://github.com/petruspierre/jedi/blob/master/nacional/resgate.ino) but this archive is incomplete.

# IFPB Alpha
- Petrus Pierre
- Yuri Monteiro
- João Rafael
- Ádisson Matheus
