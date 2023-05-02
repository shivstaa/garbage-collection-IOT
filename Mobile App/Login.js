import React from 'react';
import { View, ImageBackground, Text, Image, StyleSheet, Dimensions, SafeAreaView, TouchableHighlight, TextInput, Button} from 'react-native';
import { NavigationContainer } from '@react-navigation/native';

export default function Login({ navigation }) {
  const { width, height } = Dimensions.get('window');

  return (
      <ImageBackground
        source={require('./assets/background.png')}
        resizeMode="cover"
        style={{ width, height }}
      >
      <Text style={styles.title}>Magnify Trash</Text>         
      <TextInput
         style={styles.input}
          autoCapitalize="none"
          placeholder="Enter username"
         backgroundColor="#f5f5f5"
       />
      <TextInput
        style={styles.input}
           autoCapitalize="none"
        placeholder="Password"
        backgroundColor="#f5f5f5"
      />
      <TouchableHighlight
        activeOpacity={0.6}
        underlayColor="#DDDDDD"
        onPress={() => navigation.navigate('Home')} style={styles.button}>
        <Text style={styles.btnTitle}>Sign in</Text>
      </TouchableHighlight>
      <Text style={styles.times2}> or sign in with</Text>
      <SafeAreaView style={styles.icons}>
        <Image source={require('./assets/goog.png')}></Image>
        <Image source={require('./assets/app.png')}></Image>
        <Image source={require('./assets/fb.png')}></Image>
      </SafeAreaView>
        <Text style={styles.times}>Don't have an account yet? Sign up</Text>
      </ImageBackground>
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
    backgroundColor: '#e0e0eb',
    textAlign: 'center',
    fontFamily: 'Times New Roman',
    padding: 2,
  },
  title: {
    fontFamily: 'Times New Roman',
    fontSize: 50,
    position: "relative",
    top: 100,
    left: 50,
  },
  times: {
    fontFamily: 'Times New Roman',
    fontSize: 15,
    position: 'relative',
    top: 400,
    left: 80,
    color: "#707070",

  },
  times2: {
    fontFamily: 'Times New Roman',
    fontSize: 15,
    position: 'relative',
    top: 350,
    left: 150,
    color: "#707070",

  },
  btnTitle: {
    fontFamily: 'Times New Roman',
    color: 'white',
    marginTop: 2,
    fontSize: 16,
    fontWeight: 'bold',
    textAlign: 'center',

  },
  button: {
    position: "top",
    left: 100,
    top: 340,
    width: 193,
    height: 29,
    borderRadius: 10,
    backgroundColor: "rgba(104,139,88,1)",
  },
  icons: {
    display: "flex",
    flexDirection: "row",
    position: "relative",
    top: 370,
    justifyContent: "space-evenly"
  }
});