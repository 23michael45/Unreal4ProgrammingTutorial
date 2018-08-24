import tensorflow as tf
from tensorflow.examples.tutorials.mnist import input_data
import unreal_engine as ue
import numpy as np
import scipy as sp
import scipy.misc
from scipy.misc import imresize
#from scipy.misc import imread, imsave, imresize

from tensorflow.python.framework.graph_util import convert_variables_to_constants
class MnistComponent:
    
    def begin_play(self):

        self.actor = self.uobject.get_owner()
        self.actor.bind_event('OnPredictEvent', self.on_predict)
        self.data_path = ue.get_content_dir() + 'Scripts/MNIST_data'
        self.mnist = input_data.read_data_sets(self.data_path, one_hot=True)
        tf.reset_default_graph()
        #self.train()
        #self.predictimg()
        #self.trainCnn()

    def trainCnn(self):
        print("MnistCoponent Train Cnn Start")
        
        learning_rate = 0.001
        is_training = True
        dropout = 0.25 # Dropout, probability to drop a unit
        num_classes = 10 # MNIST total classes (0-9 digits)
        x = tf.placeholder("float", [None, 28,28,1],name = "x")
        y_ = tf.placeholder("float", [None,10],name = "y_")

         # Convolution Layer with 32 filters and a kernel size of 5
        conv1 = tf.layers.conv2d(x, 32, 5, activation=tf.nn.relu)
        # Max Pooling (down-sampling) with strides of 2 and kernel size of 2
        conv1 = tf.layers.max_pooling2d(conv1, 2, 2)

        # Convolution Layer with 64 filters and a kernel size of 3
        conv2 = tf.layers.conv2d(conv1, 64, 3, activation=tf.nn.relu)
        # Max Pooling (down-sampling) with strides of 2 and kernel size of 2
        conv2 = tf.layers.max_pooling2d(conv2, 2, 2)

        # Flatten the data to a 1-D vector for the fully connected layer
        fc1 = tf.contrib.layers.flatten(conv2)

        # Fully connected layer (in tf contrib folder for now)
        fc1 = tf.layers.dense(fc1, 1024)
        # Apply Dropout (if is_training is False, dropout is not applied)
        fc1 = tf.layers.dropout(fc1, rate=dropout, training=is_training)

        # Output layer, class prediction
        fc = tf.layers.dense(fc1, num_classes)
        #fc = tf.nn.relu(fc)
        y = tf.nn.softmax(fc)
        y = tf.identity(y, name="y")

        

        #choose one of below,they are equal
        loss_op = tf.reduce_mean(-tf.reduce_sum(y_*tf.log(y),1))
        #loss_op = tf.reduce_mean(tf.nn.sparse_softmax_cross_entropy_with_logits(logits=fc, labels=tf.cast(tf.argmax(y_,1), dtype=tf.int32)))
        
        
        optimizer = tf.train.AdamOptimizer(learning_rate=learning_rate)
        train_step = optimizer.minimize(loss_op,global_step=tf.train.get_global_step())

        # Evaluate the accuracy of the model
        accuracy, accuracy_op= tf.metrics.accuracy(labels=tf.argmax(y_,1), predictions=tf.argmax(y,1))
       
        sess = tf.Session()
        sess.run(tf.global_variables_initializer())
        sess.run(tf.local_variables_initializer())
        for i in range(1000):
            batch_xs, batch_ys = self.mnist.train.next_batch(100)
            batch_xs = np.reshape(batch_xs,(-1,28,28,1))
            [t,e,r] = sess.run([train_step,loss_op,y], feed_dict={x: batch_xs, y_: batch_ys})
            
            print("step:{} {}".format(i,e))

            #print("Cnn Step:" + str(i) +  " Accuracy:" + str(result));


        testimages = self.mnist.test.images
        testimages = np.reshape(testimages,(-1,28,28,1))
        result = sess.run([accuracy,accuracy_op], feed_dict={x: testimages, y_: self.mnist.test.labels})
        print("Cnn Final Accuracy:" + str(result))

     

        saver = tf.train.Saver()
        graph = convert_variables_to_constants(sess, sess.graph_def, ["y"])
        tf.train.write_graph(graph, self.data_path, 'mnist-cnn-graph.pb', as_text=False)

       
        pass



    def train(self):
        ue.log("MnistComponent Train Start")



        x = tf.placeholder("float", [None, 784],name = "x")
        y_ = tf.placeholder("float", [None,10],name = "y_")


        W = tf.Variable(tf.zeros([784,10]),name = "W")
        b = tf.Variable(tf.zeros([10]),name = "b")

        y = tf.nn.softmax(tf.matmul(x,W) + b,name = 'y')


        cross_entropy = -tf.reduce_sum(y_*tf.log(y))

        train_step = tf.train.GradientDescentOptimizer(0.01).minimize(cross_entropy)



        correct_prediction = tf.equal(tf.argmax(y,1), tf.argmax(y_,1))
        accuracy = tf.reduce_mean(tf.cast(correct_prediction, "float"))

        init = tf.initialize_all_variables()

        sess = tf.Session()
        sess.run(init)

        for i in range(1000):
            batch_xs, batch_ys = self.mnist.train.next_batch(100)
            sess.run(train_step, feed_dict={x: batch_xs, y_: batch_ys})


        result = sess.run(accuracy, feed_dict={x: self.mnist.test.images, y_: self.mnist.test.labels})


        ue.log("Final Accuracy:" + str(result));

        saver = tf.train.Saver()
        graph = convert_variables_to_constants(sess, sess.graph_def, ["y"])
        tf.train.write_graph(graph, self.data_path, 'mnist-graph.pb', as_text=False)

        op = sess.graph.get_operations()
        
        print("Ops----------------------------------------------------------------------------------" + str(len(op)))
        for n in op:
            #pass
            ue.log(n.name)
        print("----------------------------------------------------------------------------------")

        pass

    def predict(self,image):
        
        ue.log("MinstComponent Predict Start")
        with tf.device('/cpu:0'):
            with tf.Session() as sess:
                 with open(self.data_path + '/mnist-graph.pb', 'rb') as f:
                    graph_def = tf.GraphDef()
                    graph_def.ParseFromString(f.read()) 

        
                    graph = tf.import_graph_def(graph_def, return_elements=['y:0']) 

                    op = sess.graph.get_operations()
                    print("Ops----------------------------------------------------------------------------------"+ str(len(op)))                  
                    for n in op:
                        ue.log(n.name)
                    print("----------------------------------------------------------------------------------")

        
                    W = sess.graph.get_tensor_by_name('import/W:0')
                    b = sess.graph.get_tensor_by_name('import/b:0')
                    x = sess.graph.get_tensor_by_name('import/x:0')
                    #y_ = sess.graph.get_tensor_by_name('y_')
                    y = sess.graph.get_tensor_by_name('import/y:0')

                    
        
                   
                    image = np.reshape(image,(1,784))
                    ret = sess.run(y, feed_dict={x: image})
                    ret = np.argmax(ret,1)
                    
                    ue.log("MinstComponent Predict End:" + str(ret))

                    return ret;

        pass
    def predictCnn(self,image):
        
        ue.log("MinstComponent Predict Cnn Start")
        with tf.device('/cpu:0'):
            with tf.Session() as sess:
                 with open(self.data_path + '/mnist-cnn-graph.pb', 'rb') as f:
                    graph_def = tf.GraphDef()
                    graph_def.ParseFromString(f.read()) 

        
                    graph = tf.import_graph_def(graph_def, return_elements=['y:0']) 

                    op = sess.graph.get_operations()
                    print("Ops----------------------------------------------------------------------------------"+ str(len(op)))                  
                    for n in op:
                        ue.log(n.name)
                    print("----------------------------------------------------------------------------------")

                    x = sess.graph.get_tensor_by_name('import/x:0')
                    y = sess.graph.get_tensor_by_name('import/y:0')

                    
                    image = np.reshape(image,(-1,28,28,1))
                    ret = sess.run(y, feed_dict={x: image})
                    ret = np.argmax(ret,1)
                    
                    ue.log("MinstComponent Predict Cnn End:" + str(ret))

                    return ret;

        pass
    def predictimg(self):
         testimages = self.mnist.test.images;
         label = self.mnist.test.labels[0,:]
         ue.log(testimages.shape)
         image = testimages[0,:]
         self.predict(image)


    def on_predict(self, image):
        image = np.reshape(image,(256,256))
        image = imresize(image,(28,28))
        ue.log(image)
        image = 1 - image/255

        ue.log("On Python Predict!")
        #self.predict(image)
        self.predictCnn(image)