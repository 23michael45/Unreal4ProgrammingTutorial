import tensorflow as tf
import unreal_engine as ue
from TFPluginAPI import TFPluginAPI

class ExampleAPI(TFPluginAPI):

	#expected optional api: setup your model for training
	def onSetup(self):
		self.sess = tf.InteractiveSession()

		self.a = tf.placeholder(tf.float32)
		self.b = tf.placeholder(tf.float32)

		#operation
		self.c = self.a + self.b
		pass
		
	#expected optional api: json input as a python object, get a and b values as a feed_dict
	def onJsonInput(self, jsonInput):
		
		#show our input in the log
		print(jsonInput)

		#map our passed values to our input placeholders
		feed_dict = {self.a: jsonInput['a'], self.b: jsonInput['b']}

		#run the calculation and obtain a result
		rawResult = self.sess.run(self.c,feed_dict)
		
		#convert to array and embed the answer as 'c' field in a python object
		return {'c':rawResult.tolist()}

	#custom function to change the operation type
	def changeOperation(self, type):
		if(type == '+'):
			self.c = self.a + self.b

		elif(type == '-'):
			self.c = self.a - self.b


	#expected optional api: We don't do any training in this example
	def onBeginTraining(self):
		pass
    
#NOTE: this is a module function, not a class function. Change your CLASSNAME to reflect your class
#required function to get our api
def getApi():
	#return CLASSNAME.getInstance()
	return ExampleAPI.getInstance()