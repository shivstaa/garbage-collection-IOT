import React from 'react';
import { View, TouchableOpacity, Image } from 'react-native';

const Footer = ({ navigation, topVal }) => {
  return (
    <View style={{ flexDirection: 'row', justifyContent: 'space-evenly', position: "relative", top: topVal, backgroundColor: "white" }}>
      <TouchableOpacity onPress={() => navigation.navigate('History')}>
         <Image
        source={require('./assets/mapi.png')}
      />
      </TouchableOpacity>
      <TouchableOpacity onPress={() => navigation.navigate('Home')}>
         <Image
        source={require('./assets/homi.png')}
      />
      </TouchableOpacity>
      <TouchableOpacity onPress={() => navigation.navigate('Achivements')}>
        <Image
        source={require('./assets/stari.png')}
      />
      </TouchableOpacity>
    </View>
  );
};

export default Footer;