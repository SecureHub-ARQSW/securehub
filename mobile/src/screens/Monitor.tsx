import React from 'react';
import {StyleSheet, View, Text} from 'react-native';

function MonitorScreen(): JSX.Element {
  return (
    <View style={styles.container}>
      <Text style={styles.text}>Monitor</Text>
    </View>
  );
}

const styles = StyleSheet.create({
  container: {
    flex: 1,
    alignItems: 'center',
    flexDirection: 'column',
  },
  text: {
    fontSize: 48,
    fontFamily: 'Poppins',
    fontWeight: 'bold',
    color: '#fff',
  },
});

export default MonitorScreen;
