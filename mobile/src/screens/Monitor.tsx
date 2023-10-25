import React from 'react';
import {NativeStackScreenProps} from '@react-navigation/native-stack';
import {StyleSheet, View, Text, TouchableOpacity} from 'react-native';
import Icon from 'react-native-vector-icons/Feather';

interface MonitorScreenProps extends NativeStackScreenProps<any, 'Monitor'> {}

function MonitorScreen({navigation}: MonitorScreenProps): JSX.Element {
  return (
    <View style={styles.container}>
      <TouchableOpacity
        style={styles.wrapperIcon}
        onPress={() => navigation.goBack()}>
        <Icon name="arrow-left" size={24} color="#fff" />
      </TouchableOpacity>
      <Text style={styles.title}>MONITORE A TEMPERATURA</Text>
      <Text style={styles.description}>
        Aqui você monitora a temperatura do seu ambiente
      </Text>
      <View style={styles.boxTemperature}>
        <Icon name="thermometer" size={48} color="#fff" />
        <Text style={styles.textTemperature}>Temperatura atual:</Text>
        <Text style={styles.valueTemperature}>20°C</Text>
      </View>
    </View>
  );
}

const styles = StyleSheet.create({
  container: {
    flex: 1,
    paddingHorizontal: 32,
    marginTop: 64,
  },
  wrapperIcon: {
    backgroundColor: 'transparent',
    marginBottom: 26,
  },
  title: {
    fontSize: 32,
    fontFamily: 'Poppins',
    fontWeight: 'bold',
    color: '#fff',
  },
  description: {
    fontSize: 16,
    fontFamily: 'Inter',
    fontWeight: '500',
    color: '#7A838B',
    marginTop: 16,
    width: 240,
  },
  scrollViewContainer: {
    marginTop: 32,
  },
  boxTemperature: {
    backgroundColor: '#3F454B',
    width: '100%',
    height: 200,
    alignItems: 'center',
    justifyContent: 'center',
    alignSelf: 'center',
    borderRadius: 8,
    marginTop: 64,
  },
  textTemperature: {
    fontSize: 16,
    fontFamily: 'Inter',
    fontWeight: 'bold',
    color: '#fff',
    marginTop: 16,
  },
  valueTemperature: {
    marginTop: 16,
    fontSize: 48,
    fontFamily: 'Inter',
    fontWeight: 'bold',
    color: '#D47C31',
  },
});

export default MonitorScreen;
