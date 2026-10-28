# Changelog

## 0.1.1.0

Needs BradMick's HeliSim 1.4.3.0.

### Engine
- **Starts stay inside the TOT limits in every environment.** Start fuel is lower, so the
  start peaks under 749 C even with the power lever brought to IDLE straight after START -
  about 634 C on a standard day, 717 C in Central Asia summer. Before, a start at altitude
  sat over 749 C past its 6 s allowance and damaged the engine. A start takes about 3 s longer.

### Flight controls
- **Tail rotor authority** down about 23% from 0.1.0.0 (30% less, then 10% back), after
  flight tests.

## 0.1.0.0

- First release: the OH-6A's own flight model - T63-A-5A engine, rotors fitted to the hover
  and cruise data, mass and balance, fuel, boost-only flight controls. Needs BradMick's
  HeliSim 1.4.2.0.
