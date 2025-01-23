byte_sequence = b'\xee\x85\x9f'
try:
    decoded = byte_sequence.decode('utf-8')
    print(decoded)
except UnicodeDecodeError as e:
    print(f"解码错误: {e}")