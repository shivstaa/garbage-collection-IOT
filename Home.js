import { useState, useEffect } from 'react';
import { Dimensions, StyleSheet, SafeAreaView, ImageBackground, Text, TouchableHighlight } from 'react-native';
import { collection, doc, onSnapshot } from 'firebase/firestore';
import { db } from './firebase';
import Footer from "./Footer";

export default function Home({ navigation }) {
  const { width, height } = Dimensions.get('window');
  const [cans, setCans] = useState(0);
  const [cardboard, setCardboard] = useState(0);
  const [garbage, setGarbage] = useState(0);
  const [glass, setGlass] = useState(0);
  const [paper, setPaper] = useState(0);
  const [plastic, setPlasticBottles] = useState(0);
  const [notRecyclable, setNotRecyclable] = useState(0);
   const [recyclable, setRecyclable] = useState(0);

  useEffect(() => {
      const numbersRef = doc(collection(db, 'numbers'), 'numberDoc');
      const unsubscribe = onSnapshot(numbersRef, (doc) => {
        if (doc.exists()) { // check if the document exists
          const data = doc.data();
          if (data && data.number) { // check if the number property exists
             setCans(data.cans);
            setCardboard(data.cardboard);
            setGarbage(data.garbage);
            setGlass(data.glass);
            setPaper(data.paper);
            setPlasticBottles(data.plastic);
            setNotRecyclable(data.notRecyclable);
            setRecyclable(data.recyclable);
              }
        }
      });
      return unsubscribe;
    }, []);


  return (
    <SafeAreaView style={styles.container}>
      <ImageBackground
        source={require('./home3.png')}
        resizeMode="cover"
        style={{ width, height }}
      >
       <Text style={styles.metrics1}>{plastic} of bottles</Text>
       <Text style={styles.metrics2}>{garbage} of garbage</Text>
       <Text style={styles.metrics3}>{cans} of cans</Text>
       
       <TouchableHighlight
        onPress={() => navigation.navigate('Map')} style={styles.button}>
        <Text style={styles.btnTitle}>More..</Text>
      </TouchableHighlight>
        <TouchableOpacity onPress={() => navigation.navigate('Login')}>
         <Image
        source={require('./close2.png')}
      />
      </TouchableOpacity>
      <Footer navigation={navigation} topVal={400}/>
      </ImageBackground>
    </SafeAreaView>
  );
}

const styles = StyleSheet.create({
  container: {
    flex: 1,
    justifyContent: 'center',
  },
  input: {
    position: 'relative',
    top: 300,
    left: 100,
    height: 40,
    width: '50%',
    borderWidth: 0,
    paddingBottom: 6,
    borderRadius: 5,
    backgroundColor: '#f5f5f5',
    textAlign: 'center',
  },
  metrics1: {
    position: 'relative',
    top: 300,
    left: 60,
    color: "#C8A6FF",
    fontWeight: 'bold',
  },
   metrics2: {
    top: 284,
    left: 220,
    position: 'relative',
    color: "#C8A6FF",
    fontWeight: 'bold',
  },
   metrics3: {
    top: 510,
    left: 60,
    position: 'relative',
    color: "#C8A6FF",
    fontWeight: 'bold',
  },
  button: {
    fontFamily: "Arial", 
    position: "relative",
    top: 330,
    left: 210,
    width: 126,
    height: 161,
    borderRadius: 10,
    backgroundColor: "#C8A6FF",
    shadowOffset: {
      width: 0,
      height: 10,
    },
    shadowOpacity: 0.5,
    shadowRadius: 10,
  },
   btnTitle: {
    fontFamily: 'Times New Roman',
    color: 'white',
    marginTop: 70,
    fontSize: 16,
    textAlign: 'center',

  },
});