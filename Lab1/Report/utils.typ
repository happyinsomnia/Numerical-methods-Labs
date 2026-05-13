#let buildDiff(data_y) = {
  let diffs = ()
  let prev = ()

  for k in range(0, data_y.len() - 1) {
    if k == 0 { prev = data_y } else { prev = diffs.at(k - 1) }
    let current = ()

    for i in range(1, prev.len()) {
      current.push(
        calc.round(
          (prev.at(i) - prev.at(i - 1)) * 1000000,
        )
          / 1000000,
      )
    }
    diffs.push(current)
  }
  
  diffs
}

#let buildDivid(x, y) = {
  let n = y.len()


  let current = y
  let coef = (y.at(0),)

  for level in range(1, n) {
    let next = ()

    for i in range(0, current.len() - 1) {
      let value = (
        (
          current.at(i + 1) - current.at(i)
        )
          / (
            x.at(i + level) - x.at(i)
          )
      )

      next.push(value)
    }

    coef.push(next.at(0))
    current = next
  }

  coef
}

#let create_table(knots, data_y, diffs) = {
  let columns = 3 + diffs.len()
  table(
    columns: columns,
    align: center + horizon,
    stroke: (x, y) => {
      (
        top: if y == 0 { 1pt },
        left: if x >= 0 { 1pt },
        right: if x == columns - 1 { 1pt },
        bottom: if y == 0 or y == columns - 2 { 1pt },
      )
    },
    inset: 10pt,

    // ---------- HEADER ----------
    [$i$],
    [$x$],
    [$y$],

    ..range(diffs.len()).map(i => {
      let power = if i == 0 { "" } else { str(i + 1) }
      [$Delta^#power y$]
    }),

    // ---------- ROWS ----------
    ..range(knots.len())
      .map(i => {
        (
          [#(i + 1)],
          [#knots.at(i)],
          [#data_y.at(i)],
          ..range(diffs.len()).map(j => {
            if i < diffs.at(j).len() {
              [#diffs.at(j).at(i)]
            } else { [] }
          }),
        )
      })
      .flatten()
  )
}
