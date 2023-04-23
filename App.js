import { StatusBar } from 'expo-status-bar';
import React from 'react';
import { StyleSheet, Text, View } from 'react-native';
import Login from "./Login";
import Home from "./Home";
import Map from "./Map";
import Footer from "./Footer";
import History from "./History"; 
import Achivements from "./Achivements"; 
import Rewards from "./Rewards"; 
import { NavigationContainer } from '@react-navigation/native';
import { createStackNavigator } from '@react-navigation/stack';

function MyStack() {
  return (
    <Stack.Navigator
     screenOptions={{
        headerShown: false,
        footer: (props) => <Footer {...props} />,
      }}
    >
      <Stack.Screen name="Login" component={Login} />
      <Stack.Screen name="Home" component={Home} />
      <Stack.Screen name="Map" component={Map} />
      <Stack.Screen name="History" component={History} />
      <Stack.Screen name="Rewards" component={Rewards} />
      <Stack.Screen name="Achivements" component={Achivements} />
    </Stack.Navigator>
  );
}

const Stack = createStackNavigator();

export default function App() {
  return (
    <NavigationContainer>
      <MyStack />
     </NavigationContainer>
    
  );
}

const styles = StyleSheet.create({
  container: {
    flex: 1,
    backgroundColor: '#fff',
    alignItems: 'center',
    justifyContent: 'center',
  },
});


