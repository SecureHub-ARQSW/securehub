interface GetOptionsFilter {
  query?:
    | 'count'
    | 'min'
    | 'max'
    | 'avg'
    | 'sum'
    | 'last_item'
    | 'last_location'
    | 'aggregate'
    | 'conditional';

  variables?: string;
  start_date?: string;
  end_date?: string;
  qty?: number;
  details?: boolean;
  ordination?: 'ascending' | 'descending';
  values?: any;
  groups?: string;
}

export function tagoIOServices() {
  async function sendData(value: string, variable: string, topic: string) {
    const response = await fetch('https://api.tago.io/data', {
      method: 'POST',
      headers: {
        'Content-Type': 'application/json',
        'Device-Token': '0b85a2cd-8762-4c97-a960-35c34f7bb9c0',
      },
      body: JSON.stringify([
        {
          variable,
          value,
          metadata: {
            topic,
          },
        },
      ]),
    });

    const data = await response.json();

    return data;
  }

  async function getData(options: GetOptionsFilter) {
    try {
      const params = new URLSearchParams(options as any).toString();

      const response = await fetch(`https://api.tago.io/data?${params}`, {
        method: 'GET',
        headers: {
          'Content-Type': 'application/json',
          'Device-Token': '0b85a2cd-8762-4c97-a960-35c34f7bb9c0',
        },
      });

      const data = await response.json();

      return data;
    } catch (error: any) {
      return Promise.reject(error);
    }
  }

  return {
    sendData,
    getData,
  };
}
