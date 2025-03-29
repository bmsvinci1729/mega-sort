import random
import string
import argparse

def generate_random_string(m):
    # Ensure minimum length of 4
    length = random.randint(4, m)
    
    # First character must be an alphabet
    first_char = random.choice(string.ascii_letters)
    
    # Remaining characters can be alphanumeric or special characters
    allowed_chars = string.ascii_letters + string.digits + string.punctuation
    remaining_chars = ''.join(random.choices(allowed_chars, k=length-1))
    
    return first_char + remaining_chars

def generate_file(n, m, filename="output.txt"):
    with open(filename, "w") as file:
        for _ in range(n):
            file.write(generate_random_string(m) + "\n")
    print(f"File '{filename}' generated with {n} lines.")

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Generate a text file with random strings.")
    parser.add_argument("n", type=int, help="Number of lines")
    parser.add_argument("m", type=int, help="Maximum string length")
    parser.add_argument("--filename", type=str, default="output.txt", help="Output file name (default: output.txt)")
    
    args = parser.parse_args()
    generate_file(args.n, args.m, args.filename)
