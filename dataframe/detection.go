package dataframe

type readingState byte

const (
  ReadingInit readingState = iota
  ReadingCore
  ReadingEnd
)

func (d *Dataframe) Detect(b []byte) (i int, readed bool) {
  n := len(b)
  readed = false
  for i = 0; i < n; i++ {
    switch d.state {
    case ReadingCore:
      N := copy(d.bytes[d.index:],b[i:])
      d.index += N
      i += N
      if d.index == cap(d.bytes) {
        d.index = 0
        d.state = ReadingEnd
        d.Core.ParseBytes(d.bytes)
        readed = true
        return
      }
    /*case ReadingEnd:
      if b[i] == d.init[d.index] {
        d.index++
      }
      b[i] == 0; // cleaning buffer

      if d.index == len(d.init) {
        d.index = 0
        d.state = ReadingInit
      }*/
    default:
      if b[i] == d.init[0] {
        d.index = 1
      } else if b[i] != d.init[d.index] {
        d.index = 0
      } else {
        d.index++
      }

      if d.index == len(d.init) {
        d.index = 0
        d.state = ReadingCore
      }
    }
  }
  return
}
