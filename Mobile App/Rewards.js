import React from 'react';
import { View, ImageBackground, Text, StyleSheet, Dimensions, SafeAreaView, TextInput, TouchableHighlight} from 'react-native';
import { NavigationContainer } from '@react-navigation/native';
import Footer from "./Footer";

export default function Rewards ({ navigation }) {
  const { width, height } = Dimensions.get('window');

  return (
    <SafeAreaView style={styles.container}>
      <ImageBackground
        source={require('./assets/rewardsbg.png')}
        resizeMode="cover"
        style={{ width, height }}
      >
        <Footer navigation={navigation} topVal={620}/>
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
    top: 390,
    left: 210,
    width: 126,
    height: 161,
    borderRadius: 10,
    backgroundColor: "#C8A6FF",
  },
   btnTitle: {
    fontFamily: 'Times New Roman',
    color: 'white',
    marginTop: 70,
    fontSize: 16,
    fontWeight: 'bold',
    textAlign: 'center',

  },
});