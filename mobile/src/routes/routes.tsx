import React from 'react';
import {createNativeStackNavigator} from '@react-navigation/native-stack';
import HomeScreen from '../screens/Home';
import MonitorScreen from '../screens/Monitor';
import HistoryScreen from '../screens/History';
import StatusScreen from '../screens/Status';

const Stack = createNativeStackNavigator();

function Routes() {
  return (
    <Stack.Navigator>
      <Stack.Screen
        name="Home"
        component={HomeScreen}
        options={{
          headerShown: false,
        }}
      />
      <Stack.Screen
        name="History"
        component={HistoryScreen}
        options={{
          headerShown: false,
        }}
      />
      <Stack.Screen
        name="Status"
        component={StatusScreen}
        options={{
          headerShown: false,
        }}
      />
      <Stack.Screen
        name="Monitor"
        component={MonitorScreen}
        options={{
          headerShown: false,
        }}
      />
    </Stack.Navigator>
  );
}

export default Routes;
