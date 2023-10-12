/**
 * Sample React Native App
 * https://github.com/facebook/react-native
 *
 * @format
 */
import 'react-native-gesture-handler';
import React from 'react';
import {StatusBar, StyleSheet} from 'react-native';

import Routes from './src/routes/routes';
import {NavigationContainer} from '@react-navigation/native';
import {SafeAreaView} from 'react-native-safe-area-context';

function App(): JSX.Element {
  return (
    <NavigationContainer>
      <StatusBar barStyle="light-content" />
      <SafeAreaView style={styles.container}>
        <Routes />
      </SafeAreaView>
    </NavigationContainer>
  );
}

const styles = StyleSheet.create({
  container: {
    flex: 1,
  },
});

export default App;
