import RPi.GPIO as GPIO
import time, sys
import MorseDictionary as MD

b_pin = 23 # a gpio pin, for button
s_pin = 18 # the PWM pin, for speaker
duty_cycle = 95  # for PWM setup
frequency = 1000 # tone for the speaker to play

def to_morse(sentence, speaker, dictionary):
  for char in sentence:
    if char == ' ':
      # have been silent for letter gap for prev char
      #  now must be silet for the complete word_gap
      time.sleep(MD.word_gap-MD.letter_gap)
      sys.stdout.write('\n')
    else:
      try:
        code = dictionary[char]
        sys.stdout.write(MD.code_to_string(code))
        for delay in code:
          play_it(speaker, delay)
          time.sleep(MD.internal_gap)
        time.sleep(MD.letter_gap-MD.internal_gap)
      except KeyError:
        sys.stdout.write('\x1b[35m<\'\x1b[33m'+char+'\x1b[35m\' NOT FOUND>\x1b[0m')
      sys.stdout.write(' ')
  sys.stdout.write('\n')

def play_it(speaker, length):
  speaker.start(duty_cycle)
  time.sleep(length)
  speaker.stop()


# set pin numbering convention
GPIO.setmode(GPIO.BCM)
# setup buttons pin for input
GPIO.setup(b_pin, GPIO.IN)
# setup buzzers pin for output
GPIO.setup(s_pin, GPIO.OUT)

# PWM line setup for speaker
pwm = GPIO.PWM(s_pin, frequency)

sentence = raw_input("Enter Senctence: ").upper()
print '\x1b[32m>>> START <<<\x1b[0m'
to_morse(sentence, pwm, MD.international)
print '\x1b[31m>>> FINISH <<<\x1b[0m'


#while 1:
#  try:
#    if GPIO.input(b_pin): # Button is down
#      pwm.start(duty_cycle)
#      time.sleep(MD.time_unit)
#      pwm.stop()
#    else: # Button is up
#      print "up"
#  except KeyboardInterrupt:
#    # program quit so cleanup pwm
#    pwm.stop()
#    break;

# clean GPIO
GPIO.cleanup()
