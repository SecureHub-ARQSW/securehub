import React, {useEffect, useState} from 'react';
import {NativeStackScreenProps} from '@react-navigation/native-stack';
import {StyleSheet, View, Text, FlatList, TouchableOpacity} from 'react-native';
import Icon from 'react-native-vector-icons/Feather';
import {tagoIOServices} from '../services/tagoio';

interface DateTimeItem {
  id: string;
  dateTime: string;
  status: 'success' | 'failure';
}

interface HistoryScreenProps extends NativeStackScreenProps<any, 'History'> {}

function HistoryScreen({navigation}: HistoryScreenProps): JSX.Element {
  const [historyOfAccess, setHistoryOfAccess] = useState<DateTimeItem[]>([]);

  useEffect(() => {
    async function getData() {
      const data = await tagoIOServices().getData({
        variables: 'lock',
        qty: 10,
      });

      if (!data) {
        return;
      }

      const result = data.result.map((item: any) => ({
        id: item.id,
        // formatted value 26/09/2023 - 16:00
        dateTime: new Date(item.time).toLocaleString('pt-BR'),
        status: item.value !== '2' ? 'success' : 'failure',
      }));

      setHistoryOfAccess(result);
    }

    getData();

    /* setInterval(() => {
      getData();
    }, 1000); */
  }, []);

  const mock: DateTimeItem[] = [
    {
      id: '1',
      dateTime: '26/09/2023 - 16:00',
      status: 'success',
    },
    {
      id: '2',
      dateTime: '26/09/2023 - 16:00',
      status: 'failure',
    },
    {
      id: '3',
      dateTime: '26/09/2023 - 16:00',
      status: 'failure',
    },
  ];

  return (
    <View style={styles.container}>
      <TouchableOpacity
        style={styles.wrapperIcon}
        onPress={() => navigation.goBack()}>
        <Icon name="arrow-left" size={24} color="#fff" />
      </TouchableOpacity>
      <Text style={styles.title}>HISTÓRICO DE ACESSOS</Text>
      <Text style={styles.description}>
        Aqui você acompanha todas as movimentações que ocorreram na tranca
      </Text>
      <FlatList
        style={styles.scrollViewContainer}
        data={historyOfAccess}
        keyExtractor={item => item.id}
        renderItem={({item}) => (
          <View style={styles[item.status]}>
            <Text style={styles.dateTimeText}>{item.dateTime}</Text>
          </View>
        )}
      />
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
  success: {
    alignItems: 'center',
    justifyContent: 'center',
    backgroundColor: '#2D6A4F',
    paddingVertical: 16,
    borderRadius: 8,
    marginVertical: 8,
  },
  failure: {
    alignItems: 'center',
    justifyContent: 'center',
    backgroundColor: '#941B0C',
    paddingVertical: 16,
    borderRadius: 8,
    marginVertical: 8,
  },
  dateTimeText: {
    fontSize: 16,
    fontFamily: 'Inter',
    fontWeight: '500',
    color: '#fff',
  },
});

export default HistoryScreen;
