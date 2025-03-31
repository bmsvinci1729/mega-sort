import time
import random
import nltk
from nltk.corpus import words

# Download words dataset if not already present
nltk.download('words')
word_list = words.words()

def generate_large_text_file(filename, num_lines):
    with open(filename, 'w') as f:
        for _ in range(num_lines):
            f.write(random.choice(word_list) + '\n')

def main():
    filename = "billion_words.txt"
    num_lines = 1_000_000_000  # 1 billion
    
    start_time = time.time()
    generate_large_text_file(filename, num_lines)
    end_time = time.time()
    
    print(f"File '{filename}' generated with {num_lines} lines in {end_time - start_time:.2f} seconds.")

if __name__ == "__main__":
    main()
