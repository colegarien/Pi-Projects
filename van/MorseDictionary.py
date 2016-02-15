# Morse 1 time unit in seconds
time_unit=0.2
# Rest based on Morse standard
dit=time_unit
dah=time_unit*3
internal_gap=time_unit
letter_gap=time_unit*3
word_gap=time_unit*7
# For displaying
dit_char = '.'
dah_char = '-'

def code_to_string(delays):
  out = ""
  for d in delays:
    if d == dit:
      out += dit_char
    elif d==dah:
      out += dah_char
  return out

international = {'A': [dit,dah],
                 'B': [dah,dit,dit,dit],
                 'C': [dah,dit,dah,dit],
                 'D': [dah,dit,dit],
                 'E': [dit],
                 'F': [dit,dit,dah,dit],
                 'G': [dah,dah,dit],
                 'H': [dit,dit,dit,dit],
                 'I': [dit,dit],
                 'J': [dit,dah,dah,dah],
                 'K': [dah,dit,dah],
                 'L': [dit,dah,dit,dit],
                 'M': [dah,dah],
                 'N': [dah,dit],
                 'O': [dah,dah,dah],
                 'P': [dit,dah,dah,dit],
                 'Q': [dah,dah,dit,dah],
                 'R': [dit,dah,dit],
                 'S': [dit,dit,dit],
                 'T': [dah],
                 'U': [dit,dit,dah],
                 'V': [dit,dit,dit,dah],
                 'W': [dit,dah,dah],
                 'X': [dah,dit,dit,dah],
                 'Y': [dah,dit,dah,dah],
                 'Z': [dah,dah,dit,dit],
                 '1': [dit,dah,dah,dah,dah],
                 '2': [dit,dit,dah,dah,dah],
                 '3': [dit,dit,dit,dah,dah],
                 '4': [dit,dit,dit,dit,dah],
                 '5': [dit,dit,dit,dit,dit],
                 '6': [dah,dit,dit,dit,dit],
                 '7': [dah,dah,dit,dit,dit],
                 '8': [dah,dah,dah,dit,dit],
                 '9': [dah,dah,dah,dah,dit],
                 '0': [dah,dah,dah,dah,dah],
                 '.': [dit,dah,dit,dah,dit,dah],
                 ',': [dah,dah,dit,dit,dah,dah],
                 '?': [dit,dit,dah,dah,dit,dit],
                 '\'': [dit,dah,dah,dah,dah,dit],
                 '!': [dah,dit,dah,dit,dah,dah],
                 '/': [dah,dit,dit,dah,dit],
                 '(': [dah,dit,dah,dah,dit],
                 ')': [dah,dit,dah,dah,dit,dah],
                 '&': [dit,dah,dit,dit,dit],
                 ':': [dah,dah,dah,dit,dit,dit],
                 ';': [dah,dit,dah,dit,dah,dit],
                 '=': [dah,dit,dit,dit,dah],
                 '+': [dit,dah,dit,dah,dit],
                 '-': [dah,dit,dit,dit,dit,dah],
                 '_': [dit,dit,dah,dah,dit,dah],
                 '\"': [dit,dah,dit,dit,dah,dit],
                 '$': [dit,dit,dit,dah,dit,dit,dah],
                 '@': [dit,dah,dah,dit,dah,dit]}
