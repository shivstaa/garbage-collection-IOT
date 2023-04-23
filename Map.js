import React from 'react';
import { View, ImageBackground, Image, Text, StyleSheet, Dimensions, SafeAreaView, TextInput, TouchableHighlight} from 'react-native';
import { NavigationContainer } from '@react-navigation/native';
import Footer from "./Footer";

export default function Map ({ navigation }) {
  const { width, height } = Dimensions.get('window');

  return (
    <SafeAreaView style={styles.container}>
      <ImageBackground
        source={require('./assets/map.png')}
        resizeMode="cover"
        style={{ width, height }}
      >
      <TouchableHighlight onPress={() => navigation.navigate('Achivements')}>
         <Image
            style={styles.img}
            source={require('./historycomponent.png')}
        />
      </TouchableHighlight>
      <Footer navigation={navigation} topVal={587}/>
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
  img: {
    position: "relative",
    top: 580,
    left: 160,

  },
   btnTitle: {
    fontFamily: 'Times New Roman',
    color: 'white',
    marginTop: 2,
    fontSize: 16,
    fontWeight: 'bold',
    textAlign: 'center',

  },
});