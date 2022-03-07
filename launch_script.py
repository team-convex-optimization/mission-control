from gpiozero import Button
import os, subprocess, time

B_SHUTDOWN = Button(21) 	 # Shutdown read pin
B_RACE_PIPELINE = Button(22) # What script to run on raceday
B_TEST_PIPELINE = Button(23) # Script to run on testing

current_pipeline = None

def shutdown():
	os.system("sudo shutdown now")

def race_pipeline():
	global current_pipeline
	kill_pipeline()
	current_pipeline = subprocess.Popen(["sh", "race.sh"])

def test_pipeline():
	global current_pipeline
	kill_pipeline()
	current_pipeline = subprocess.Popen(["sh", "test.sh"])

def kill_pipeline():
	global current_pipeline
	if current_pipeline is not None:
		current_pipeline.kill()
	subprocess.run(["sh", "clean.sh"])

B_SHUTDOWN.when_pressed = shutdown()
B_RACE_PIPELINE.when_pressed = race_pipeline()
B_TEST_PIPELINE.when_pressed = test_pipeline()

while True:				# Wait indefinetly 
	time.sleep(300)
