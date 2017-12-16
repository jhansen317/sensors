from flask import Flask, g
import json
import logging
from datetime import date, datetime
import time
from pymongo import MongoClient

logging.basicConfig(level=logging.DEBUG)
LOGGER = logging.getLogger(__name__)

def json_serial(obj):
    """JSON serializer for objects not serializable by default json code"""

    if isinstance(obj, (datetime, date)):
        return int(time.mktime(obj.timetuple())) * 1000
    raise TypeError ("Type %s not serializable" % type(obj))

app = Flask(__name__)

def get_mongo_db():
    if not hasattr(g, 'mongo_db'):
        g.mongo_db = MongoClient('localhost', username='www', password='webmongo', authSource='sensors').sensors
    return g.mongo_db


@app.route("/sensors/environment")
def environment():
    mdb = get_mongo_db()
    data = [d for d in mdb.environment.find(projection={'_id':False})]
    resp = json.dumps(data, default=json_serial)
    return (resp, 200, {'Content-type': 'application/json'})

@app.route("/sensors/environment/limit/<int:records>")
def environment_limit(records):
    mdb = get_mongo_db()
    data = [d for d in mdb.environment.find(sort=[('_id', -1)], limit=records, projection={'_id':False})]
    data.reverse()
    resp = json.dumps(data, default=json_serial)
    return (resp, 200, {'Content-type': 'application/json'})


if __name__ == "__main__":
    app.run(debug=True)
