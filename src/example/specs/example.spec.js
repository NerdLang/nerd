import { sum, fibonacci } from '../example'

describe('Example', () => {
  it('should sum all arguments', () => {
    expect(sum(1, 2, 3)).toEqual(6)
  })

  it('should return [0, 1]', () => {
    expect(fibonacci().next().value).toEqual([0, 1])
  })

  it('should follow fibonacci', () => {
    const gen = fibonacci()

    expect(gen.next().value).toEqual([0, 1])
    expect(gen.next().value).toEqual([1, 1])
    expect(gen.next().value).toEqual([1, 2])
    expect(gen.next().value).toEqual([2, 3])
    expect(gen.next().value).toEqual([3, 5])
    expect(gen.next().value).toEqual([5, 8])
    expect(gen.next().value).toEqual([8, 13])
    expect(gen.next().value).toEqual([13, 21])
    expect(gen.next().value).toEqual([21, 34])
  })
})
