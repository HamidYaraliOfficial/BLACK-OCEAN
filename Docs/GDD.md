# BLACK OCEAN — Game Design Document (Summary)

## Concept
BLACK OCEAN is a Modern Naval Strategy / Tactical Fleet Command / Maritime
Simulation set in an entirely fictional world. The player commands a fictional
naval fleet, balancing operations, logistics, economy, research, diplomacy
and long-term fleet development across a persistent, living ocean world.

All nations, vessels, weapons, sensors and organizations in BLACK OCEAN are
invented for gameplay purposes. Nothing in this project models real-world
military hardware, doctrine or operational procedures.

## Pillars
1. **Systemic depth over scripted set-pieces** — the world reacts to player
   decisions through interconnected economy, logistics, diplomacy and
   readiness systems, not one-off scripted events.
2. **Imperfect information** — the player and AI alike act only on what
   sensors have actually detected (see `Source/BlackOcean/Sensors`), never
   on hidden ground truth.
3. **Consequential command** — orders take time to arrive (Command Delay
   System) and ships carry persistent state between missions, so decisions
   compound over a campaign rather than resetting each mission.

## Core Loop
Strategic Globe → Fleet Planning → Mission Briefing → Navigation → Recon →
Maritime Operation → Damage/Repair → Logistics → Port Management → Research →
Diplomacy → Fleet Modernization → Campaign Progression → (repeat, world
state carried forward).

## Systems Implemented in This Scaffold
See `README (1).markdown` for the full list mapped to source folders. This
document covers design intent; `Docs/TechnicalDesign.md` covers architecture.

## Scope Note
This repository is an architectural foundation: core gameplay systems are
implemented with real logic in C++ and are ready to extend, but a full
AAA-scale release (complete art, VO, hundreds of hours of content, full
multiplayer) requires a full production team and is outside what any single
delivery can produce. Treat this as the systems foundation to build on.
