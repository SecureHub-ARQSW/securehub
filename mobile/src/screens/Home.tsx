import {NativeStackScreenProps} from '@react-navigation/native-stack';
import React from 'react';
import {StyleSheet, View, Text, TouchableOpacity} from 'react-native';
import Icon from 'react-native-vector-icons/Feather';

interface HomeScreenProps extends NativeStackScreenProps<any, 'Home'> {}

function HomeScreen({navigation}: HomeScreenProps): JSX.Element {
  return (
    <View style={styles.container}>
      <Text style={styles.title}>BEM-VINDO AO SECUREHUB</Text>
      <Text style={styles.description}>
        Seu cômodo mais seguro e automatizado
      </Text>
      <View style={styles.buttonsContainer}>
        <TouchableOpacity
          style={styles.buttonBlock}
          onPress={() => navigation.push('State')}>
          <Icon name="eye" size={24} color="#fff" />
          <Text style={styles.buttonText}>VISUALIZAR ESTADO</Text>
        </TouchableOpacity>

        <TouchableOpacity
          style={styles.buttonBlock}
          onPress={() => navigation.push('History')}>
          <Icon name="file-text" size={24} color="#fff" />
          <Text style={styles.buttonText}>VISUALIZAR HISTÓRICO</Text>
        </TouchableOpacity>

        <TouchableOpacity
          style={styles.buttonBlock}
          onPress={() => navigation.push('Monitor')}>
          <Icon name="thermometer" size={24} color="#fff" />
          <Text style={styles.buttonText}>MONITORAR TEMPERATURA</Text>
        </TouchableOpacity>
      </View>
    </View>
  );
}

const styles = StyleSheet.create({
  container: {
    flex: 1,
    paddingHorizontal: 32,
    marginTop: 96,
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
    width: 200,
  },
  buttonsContainer: {
    gap: 16,
    marginTop: 96,
  },
  buttonBlock: {
    paddingVertical: 16,
    paddingHorizontal: 32,
    backgroundColor: '#D47C31',
    borderRadius: 8,
    flexDirection: 'row',
    alignItems: 'center',
    gap: 16,
  },
  buttonText: {
    fontWeight: 'bold',
    fontSize: 16,
    color: '#fff',
  },
});

export default HomeScreen;
