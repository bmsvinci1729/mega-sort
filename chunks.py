import os

def split_file(input_file, output_dir, target_chunk_count=100):
    os.makedirs(output_dir, exist_ok=True)

    # Step 1: Get total size of the input file
    total_size = os.path.getsize(input_file)
    chunk_size = total_size // target_chunk_count

    print(f"Total size: {total_size / (1024*1024):.2f} MB")
    print(f"Target chunks: {target_chunk_count}")
    print(f"Chunk size: {chunk_size / (1024*1024):.2f} MB")

    with open(input_file, 'r', encoding='utf-8') as infile:
        chunk_index = 0
        current_chunk_size = 0
        chunk_lines = []

        for line in infile:
            chunk_lines.append(line)
            current_chunk_size += len(line.encode('utf-8'))  # accurate byte size

            # If current chunk size exceeds target chunk size, write it
            if current_chunk_size >= chunk_size:
                with open(os.path.join(output_dir, f'chunk_{chunk_index}.txt'), 'w', encoding='utf-8') as chunk_file:
                    chunk_file.writelines(chunk_lines)
                print(f"Written chunk_{chunk_index}.txt with size ~{current_chunk_size / (1024*1024):.2f} MB")
                chunk_index += 1
                chunk_lines = []
                current_chunk_size = 0

        # Write remaining lines
        if chunk_lines:
            with open(os.path.join(output_dir, f'chunk_{chunk_index}.txt'), 'w', encoding='utf-8') as chunk_file:
                chunk_file.writelines(chunk_lines)
            print(f"Written chunk_{chunk_index}.txt (final chunk)")

if __name__ == '__main__':
    input_file = 'data/input_1B.txt'
    output_dir = 'chunks'
    split_file(input_file, output_dir, target_chunk_count=120)
