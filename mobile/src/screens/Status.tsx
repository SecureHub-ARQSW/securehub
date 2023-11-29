import React, {useEffect, useState} from 'react';
import {NativeStackScreenProps} from '@react-navigation/native-stack';
import {
  StyleSheet,
  View,
  Text,
  TouchableOpacity,
  Modal,
  TextInput,
} from 'react-native';
import Icon from 'react-native-vector-icons/Feather';
import {tagoIOServices} from '../services/tagoio';
import {showMessage} from 'react-native-flash-message';

interface StatusScreenProps extends NativeStackScreenProps<any, 'Status'> {}

function StatusScreen({navigation}: StatusScreenProps): JSX.Element {
  const [statusLock, setStatusLock] = useState<'on' | 'off'>('off');
  const [isVisibleModal, setIsVisibleModal] = useState(false);
  const [password, setPassword] = useState('');

  /*  function openModal() {
    setIsVisibleModal(true);
  } */

  function closeModal() {
    setIsVisibleModal(false);
  }

  async function sendLockStatus() {
    const responseData = await tagoIOServices().sendData(
      password,
      'lock',
      'info/lock',
    );

    if (!responseData.status) {
      showMessage({
        message: 'Erro ao desbloquear a tranca!',
        type: 'danger',
      });

      return;
    }

    showMessage({
      message: 'Tranca desbloqueada com sucesso!',
      type: 'success',
    });

    closeModal();
  }

  useEffect(() => {
    const mapValueOfStatusName = {
      '1': 'off',
      '0': 'on',
    };

    async function getData() {
      const data = await tagoIOServices().getData({
        variables: 'lock',
        qty: 1,
      });

      if (!data) {
        return;
      }

      const result = data.result[0].value as 1 | 0;

      console.log(result);

      const status = mapValueOfStatusName[result];

      setStatusLock(status as 'on' | 'off');
    }

    setInterval(() => {
      getData();
    }, 1000);
  }, []);

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
      <View style={styles[statusLock]}>
        <Text style={styles.statusText}>
          {statusLock === 'off' ? 'FECHADA' : 'ABERTA'}
        </Text>
      </View>
      {/* {data.status === 'lock' && (
        <TouchableOpacity style={styles.btn} onPress={openModal}>
          <Text style={styles.btnText}>DESBLOQUEAR</Text>
        </TouchableOpacity>
      )} */}
      <Modal
        animationType="slide"
        transparent={true}
        visible={isVisibleModal}
        onRequestClose={closeModal}>
        <View style={styles.centeredView}>
          <View style={styles.modalView}>
            <TextInput
              placeholder="Digite a senha"
              style={styles.textInput}
              secureTextEntry={true}
              value={password}
              onChangeText={text => setPassword(text)}
            />
            <TouchableOpacity style={styles.btn} onPress={sendLockStatus}>
              <Text style={styles.btnText}>DESBLOQUEAR</Text>
            </TouchableOpacity>
          </View>
        </View>
      </Modal>
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
  textInput: {
    backgroundColor: '#fff',
    width: 200,
    height: 50,
    borderRadius: 8,
    marginBottom: 16,
    paddingHorizontal: 16,
  },
  btnText: {
    fontSize: 16,
    fontFamily: 'Inter',
    fontWeight: 'bold',
    color: '#fff',
    textAlign: 'center',
  },
  centeredView: {
    flex: 1,
    justifyContent: 'center',
    alignItems: 'center',
    backgroundColor: '#00000099',
  },
  modalView: {
    margin: 20,
    backgroundColor: 'white',
    borderRadius: 20,
    padding: 35,
    alignItems: 'center',
  },
  button: {
    borderRadius: 20,
    padding: 10,
    elevation: 2,
  },
  buttonOpen: {
    backgroundColor: '#F194FF',
  },
  buttonClose: {
    backgroundColor: '#2196F3',
  },
  textStyle: {
    color: 'white',
    fontWeight: 'bold',
    textAlign: 'center',
  },
  modalText: {
    marginBottom: 15,
    textAlign: 'center',
  },
});

export default StatusScreen;
