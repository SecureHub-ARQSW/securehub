import React from 'react';
import {NativeStackScreenProps} from '@react-navigation/native-stack';
import {StyleSheet, View, Text, TouchableOpacity} from 'react-native';
import Icon from 'react-native-vector-icons/Feather';

interface StatusScreenProps extends NativeStackScreenProps<any, 'Status'> {}

function StatusScreen({navigation}: StatusScreenProps): JSX.Element {
  const text = {
    lock: 'BLOQUEADA',
    on: 'ABERTA',
    off: 'FECHADA',
  };

  const data: {status: 'on' | 'off' | 'lock'; text: string} = {
    status: 'lock',
    text: text.lock,
  };

  return (
    <View style={styles.container}>
      <View>
        <TouchableOpacity
          style={styles.wrapperIcon}
          onPress={() => navigation.goBack()}>
          <Icon name="arrow-left" size={24} color="#fff" />
        </TouchableOpacity>
        <Text style={styles.title}>ESTADO DA TRANCA</Text>
        <Text style={styles.description}>
          Aqui você visualiza o estado da tranca
        </Text>
      </View>
      <View style={styles[data.status]}>
        <Text style={styles.statusText}>{data.text}</Text>
      </View>
      {data.status === 'lock' && (
        <TouchableOpacity style={styles.btn}>
          <Text style={styles.btnText}>DESBLOQUEAR</Text>
        </TouchableOpacity>
      )}
    </View>
  );
}

const styles = StyleSheet.create({
  container: {
    flex: 1,
    paddingHorizontal: 32,
    marginTop: 64,
    paddingBottom: 32,
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
    width: 200,
  },
  description: {
    fontSize: 16,
    fontFamily: 'Inter',
    fontWeight: '500',
    color: '#7A838B',
    marginTop: 16,
    width: 240,
  },
  off: {
    backgroundColor: '#941B0C',
    width: 200,
    height: 200,
    alignItems: 'center',
    justifyContent: 'center',
    alignSelf: 'center',
    borderRadius: 8,
    marginTop: 64,
  },
  on: {
    backgroundColor: '#2D6A4F',
    width: 200,
    height: 200,
    alignItems: 'center',
    justifyContent: 'center',
    alignSelf: 'center',
    borderRadius: 8,
    marginTop: 64,
  },
  lock: {
    backgroundColor: '#3F454B',
    width: 200,
    height: 200,
    alignItems: 'center',
    justifyContent: 'center',
    alignSelf: 'center',
    borderRadius: 8,
    marginTop: 64,
  },
  statusText: {
    fontSize: 16,
    fontFamily: 'Inter',
    fontWeight: 'bold',
    color: '#fff',
  },
  btn: {
    backgroundColor: '#D47C31',
    paddingVertical: 16,
    paddingHorizontal: 32,
    borderRadius: 8,
    width: '100%',
    marginTop: 'auto',
  },
  btnText: {
    fontSize: 16,
    fontFamily: 'Inter',
    fontWeight: 'bold',
    color: '#fff',
    textAlign: 'center',
  },
});

export default StatusScreen;