import math


class Point:
    def __init__(self, x, y):
        self.x = x
        self.y = y


def main():
    n = int(input("Enter the value of n: "))

    radius = 1.0  # Radius of the polygon
    angle = 2 * math.pi / n  # Angle between adjacent vertices

    for i in range(n):
        x = radius * math.cos(i * angle)
        y = radius * math.sin(i * angle)
        print(f"Vertex {i + 1}: ({x}, {y})")


if __name__ == "__main__":
    main()
