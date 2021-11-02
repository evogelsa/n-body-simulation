# Notes

## Meeting 2021-10-26

### Differentiating between numerical instability vs physical instability

- If changing time step results in very different physics, this implies
numerical instability.
- As time step -> 0, then we expect physics to be "correct"

### Next steps

- Relax physical constraints:
  - Take bodies off of a plane
  - Explore bodies of equal mass
- Restricted 3-body problem:
  - One mass much smaller than other two
  - Satellite + earth and sun
  - Can be solved analytically through assumptions
  - Lagrange points of restricted 3-body orbit
- Explore more initial conditions:
  - See what else is available for earth and sun and satellite orbits
  - Lissajous orbit, can we reproduce?
