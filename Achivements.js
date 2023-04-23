import React from 'react';
import { View, ImageBackground, Text, StyleSheet, Dimensions, SafeAreaView, TextInput, TouchableHighlight} from 'react-native';
import { NavigationContainer } from '@react-navigation/native';

export default function Achivements ({ navigation }) {
  const { width, height } = Dimensions.get('window');

  return (
    <SafeAreaView style={styles.container}>
      <ImageBackground
        source={require('./achibg.png')}
        resizeMode="cover"
        style={{ width, height }}
      >
      <TouchableHighlight
        onPress={() => navigation.navigate('Rewards')} style={styles.button}>
        <Text style={styles.text}>All Rewards</Text>
      </TouchableHighlight>
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
  button: {
    fontFamily: "Arial", 
    position: "relative",
    top: 30,
    left: 250,
    width: 90,
    height: 30,
    borderRadius: 10,
    paddingHorizontal: 20,
    paddingVertical: 10,
    shadowColor: '#000',
    shadowOffset: {
      width: 0,
      height: 10,
    },
    shadowOpacity: 0.5,
    shadowRadius: 10,
    elevation: 5,
    backgroundColor: "#C8A6FF",
  },
   text: {
    fontFamily: 'Times New Roman',
    color: 'white',
    fontSize: 10,
    textAlign: 'center',

  },
});